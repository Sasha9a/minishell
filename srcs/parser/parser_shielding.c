/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shielding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:10:12 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:15:55 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Produces shielding
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 0 if good, otherwise -1
*/

int		get_shielding(t_all *all, char **text)
{
	if (all->line[all->pos + 1])
	{
		if (join_char(text, all->line[all->pos + 1]) == -1)
			return (-1);
		all->pos += 2;
	}
	return (0);
}

int		is_norm_shielding(t_all *all)
{
	int		i;

	i = -1;
	while (all->line[++i])
	{
		if (all->line[i] == '\\')
		{
			if (!all->line[i + 1])
				return (0);
		}
	}
	return (1);
}
