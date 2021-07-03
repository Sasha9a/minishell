/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:29:09 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:17:55 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** removes the environment variable
**
** @param *all general structure
** @param *s unset function argument
*/

static void	delete_env(t_all *all, char *s)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*parent;

	lst = all->env;
	parent = NULL;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->name, s, ft_strlen(s) + 1))
		{
			tmp = lst;
			lst = lst->next;
			if (parent)
				parent->next = lst;
			ft_lstdelone(tmp, free_t_env);
		}
		else
		{
			parent = lst;
			lst = lst->next;
		}
	}
}

/*
** executes the unset command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int			ft_unset(t_all *all, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->argv[++i])
		delete_env(all, cmd->argv[i]);
	all->res = 0;
	return (0);
}
