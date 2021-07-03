/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:38:00 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/17 21:50:30 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(unsigned char c)
{
	return (c == ' ' || c == '\n' || c == '\t' ||
		c == '\v' || c == '\f' || c == '\r');
}

static int	is_num(char *str)
{
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') && !is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

/*
** executes the exit command
**
** @param *all general structure
** @param *cmd command structure
** @return 0
*/

int			ft_exit(t_all *all, t_cmd *cmd)
{
	if (strs_size(cmd->argv) > 1)
	{
		bash_err("exit", "too many arguments", 0);
		all->res = 1;
	}
	else if (ft_strncmp(cmd->argv[0], "", 1))
	{
		if (!is_num(cmd->argv[0]))
		{
			all->res = 2;
			bash_err(cmd->argv[0], "numeric argument required", 0);
		}
		else
		{
			all->res = ft_atoi(cmd->argv[0]);
			if (all->res > 255 || all->res < 0)
				all->res = 1;
		}
	}
	clear_all(all);
	exit(all->res);
	return (0);
}
