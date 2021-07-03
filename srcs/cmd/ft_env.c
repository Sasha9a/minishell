/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:13:05 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:17:31 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** executes the env command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int		ft_env(t_all *all, t_cmd *cmd)
{
	t_list	*lst;

	(void)cmd;
	lst = all->env;
	while (lst)
	{
		if (((t_env*)lst->content)->par)
		{
			ft_putstr_fd(((t_env*)lst->content)->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(((t_env*)lst->content)->par, 1);
			ft_putstr_fd("\n", 1);
		}
		lst = lst->next;
	}
	all->res = 0;
	return (0);
}
