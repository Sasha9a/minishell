/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:34:10 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/12 15:04:10 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"

static int	wait_all(t_list *cmds)
{
	int ret;
	int status;

	ret = 0;
	while (cmds)
	{
		if (waitpid(ltoc(cmds)->pid, &status, 0) == -1)
			return (bash_err(ltoc(cmds)->name, strerror(errno), -1));
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if ((ret = WTERMSIG(status)) == 2)
				ret = 130;
		}
		else
			ret = -1;
		cmds = cmds->next;
	}
	g_state.cmdrun = 0;
	return (ret);
}

static void	fds_close(int *pipefd, int pipefd0)
{
	if (pipefd[0] != -1)
		close(pipefd[1]);
	if (pipefd0 != -1)
		close(pipefd0);
}

/*
** run_pipe
** cmds : list of cmds to pipe run
** all : is's all
** return : last process result code (or signal code) or -1 in case of error
**
** run cmds in parallel by connecting them together with pipes
** if the cmd have fd_* then it is used instead of a pipe
** if proccess stoped by signal 2, then return code 130 (like in the bash)
**
** !!! precess errors and descriptors error not considered errors
*/

int			run_pipe(t_list *cmds, t_all *all)
{
	t_list	*cmd;
	int		pipefd[2];
	int		pipefd0;

	g_state.cmdrun = 1;
	cmd = cmds;
	pipefd0 = -1;
	while (cmd)
	{
		if (!cmd->next)
			pipefd[0] = -1;
		else if (pipe(pipefd) == -1)
			return (bash_err("pipe", strerror(errno), -1));
		if ((ltoc(cmd)->pid = fork()) == -1)
			return (bash_err("fork", strerror(errno), -1));
		if (ltoc(cmd)->pid == 0)
			child_proc(pipefd, pipefd0, cmd, all);
		fds_close(pipefd, pipefd0);
		pipefd0 = pipefd[0];
		cmd = cmd->next;
	}
	if (pipefd0 != -1)
		close(pipefd0);
	return (wait_all(cmds));
}
