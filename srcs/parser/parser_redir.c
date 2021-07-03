/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:09:49 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:15:49 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_filename(t_all *all, t_cmd *cmd)
{
	const char	*spec[6] = { " ", "|", ";", "<", ">>", ">" };

	trim_space(all);
	while (all->line[all->pos])
	{
		if (is_spec(all, spec, 6))
			return (0);
		if (!get_spec(all, &((t_redir*)ft_lstlast(cmd->redirs)->content)->name))
		{
			if (join_char(&((t_redir*)ft_lstlast(cmd->redirs)->content)->name,
				all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	return (0);
}

int			parser_redir(t_all *all)
{
	t_list	*lst;
	t_cmd	*cmd;

	if (!(lst = init_redir()))
		return (-1);
	cmd = ((t_cmd*)ft_lstlast(all->cmd)->content);
	ft_lstadd_back(&cmd->redirs, lst);
	if (!ft_strncmp(&all->line[all->pos], ">>", 2))
		((t_redir*)ft_lstlast(cmd->redirs)->content)->type = 'a';
	else if (!ft_strncmp(&all->line[all->pos], ">", 1))
		((t_redir*)ft_lstlast(cmd->redirs)->content)->type = '>';
	else if (!ft_strncmp(&all->line[all->pos], "<", 1))
		((t_redir*)ft_lstlast(cmd->redirs)->content)->type = '<';
	if (((t_redir*)ft_lstlast(cmd->redirs)->content)->type == 'a')
		all->pos += 2;
	else
		all->pos++;
	if (get_filename(all, cmd) == -1)
		return (-1);
	return (0);
}
