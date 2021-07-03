/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:58:57 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/13 19:36:51 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_cmd	*ltoc(t_list *lst)
{
	return (lst->content);
}

t_redir	*ltor(t_list *lst)
{
	return (lst->content);
}

int		bash_err(char *str1, char *str2, int ret)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str1, 2);
	if (str2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	ft_putstr_fd("\n", 2);
	return (ret);
}
