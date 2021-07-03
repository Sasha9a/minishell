/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:38:32 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:13:03 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** creates a command structure
**
** @return command pointer, otherwise NULL
*/

t_list	*init_cmd(void)
{
	t_cmd	*cmd;
	t_list	*res;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = ft_strdup("");
	if (!(cmd->argv = ft_calloc(2, sizeof(char*))) ||
		!(cmd->argv[0] = ft_strdup("")))
		return (NULL);
	cmd->argv[1] = 0;
	cmd->pipe = 0;
	cmd->error = 0;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->pid = 0;
	cmd->redirs = NULL;
	if (!(res = ft_lstnew(cmd)))
		free(cmd);
	return (res);
}

t_list	*init_redir(void)
{
	t_redir	*redir;
	t_list	*res;

	if (!(redir = malloc(sizeof(t_redir))))
		return (NULL);
	redir->name = ft_strdup("");
	if (!(res = ft_lstnew(redir)))
		free(redir);
	return (res);
}
