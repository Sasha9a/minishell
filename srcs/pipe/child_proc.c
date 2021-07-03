/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:04:18 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/17 22:11:34 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void	run_proc(t_list *cmd, t_all *all)
{
	char	**envp;
	char	**argv;
	char	*fullname;

	fullname = NULL;
	argv = NULL;
	if (!(envp = convert_env(all)) ||
		!(argv = convert_argv(cmd)))
		free_local(envp, argv, &fullname, -1);
	else if (!(fullname = get_full_cmd_name(all, cmd)))
		free_local(envp, argv, &fullname, 0);
	else
	{
		execve(fullname, argv, envp);
		bash_err(ltoc(cmd)->name, strerror(errno), 0);
		if (errno == ENOENT || errno == ENOTDIR)
			all->res = 127;
		else
			all->res = 126;
		free_local(envp, argv, &fullname, 0);
	}
	clear_all(all);
	exit(all->res);
}

static void	child_proc_fds(int *pipefd, int prev_pipefd0, t_list *cmd)
{
	if (pipefd[0] != -1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
	}
	if (prev_pipefd0 != -1)
		dup2(prev_pipefd0, 0);
	if (ltoc(cmd)->fd_in != -1)
		dup2(ltoc(cmd)->fd_in, 0);
	if (ltoc(cmd)->fd_out != -1)
		dup2(ltoc(cmd)->fd_out, 1);
}

void		child_proc(int *pipefd, int prev_pipefd0, t_list *cmd, t_all *all)
{
	int		res_cmd;

	child_proc_fds(pipefd, prev_pipefd0, cmd);
	if (!ltoc(cmd)->error)
	{
		if (ltoc(cmd)->name && ft_strlen(ltoc(cmd)->name))
		{
			if ((res_cmd = start_cmd(all, cmd)) == -1)
				clear_all(all);
			if (!res_cmd)
				run_proc(cmd, all);
		}
		else
			all->res = 0;
	}
	else
		all->res = 1;
	clear_all(all);
	exit(all->res);
}
