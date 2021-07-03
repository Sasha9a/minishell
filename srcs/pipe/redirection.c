/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:23:33 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/12 10:58:24 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static void	close_fds(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	cmd->fd_out = -1;
	cmd->fd_in = -1;
}

static int	file_out(t_list *cmds, t_list *elems)
{
	int fd;

	if ((fd = open(ltoc(elems)->name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		close_fds(ltoc(cmds));
		return (bash_err(ltoc(elems)->name, strerror(errno), 0));
	}
	if (ltoc(cmds)->fd_out != -1)
		close(ltoc(cmds)->fd_out);
	ltoc(cmds)->fd_out = fd;
	return (1);
}

static int	file_in(t_list *cmds, t_list *elems)
{
	int fd;

	if ((fd = open(ltoc(elems)->name, O_RDONLY)) == -1)
	{
		close_fds(ltoc(cmds));
		return (bash_err(ltoc(elems)->name, strerror(errno), 0));
	}
	if (ltoc(cmds)->fd_in != -1)
		close(ltoc(cmds)->fd_in);
	ltoc(cmds)->fd_in = fd;
	return (1);
}

static int	file_append(t_list *cmds, t_list *elems)
{
	int fd;

	if ((fd = open(ltoc(elems)->name,
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		close_fds(ltoc(cmds));
		return (bash_err(ltoc(elems)->name, strerror(errno), 0));
	}
	if (ltoc(cmds)->fd_out != -1)
		close(ltoc(cmds)->fd_out);
	ltoc(cmds)->fd_out = fd;
	return (1);
}

/*
** handle_redir
**
** @cmds - list cmds
** @return 1 if good, otherwise 0 - file error
** solve redirs
** set new fd_in and fd_out in each t_cmd
** set cmd->error to 1, if cmd contaited bad redir file
**
** !!! Opens descriptors
*/

int			handle_redir(t_list *cmds)
{
	t_list	*elems;

	while (cmds)
	{
		elems = ltoc(cmds)->redirs;
		while (elems)
		{
			if (ltor(elems)->type == '>' && !file_out(cmds, elems))
				return (0);
			if (ltor(elems)->type == '<' && !file_in(cmds, elems))
				return (0);
			if (ltor(elems)->type == 'a' && !file_append(cmds, elems))
				return (0);
			elems = elems->next;
		}
		if (!ltoc(cmds)->name)
			close_fds(ltoc(cmds));
		cmds = cmds->next;
	}
	return (1);
}
