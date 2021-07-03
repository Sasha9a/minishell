/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:38:26 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:16:17 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** gets strings when encountering special characters
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 1 if a special character is encountered, 0 if not, -1 error
*/

int			get_spec(t_all *all, char **text)
{
	const char	spec[5] = "\\$\'\"";
	int			(*f[4])(t_all*, char**);
	int			i;

	i = -1;
	f[0] = get_shielding;
	f[1] = get_variables;
	f[2] = get_strong_quotes;
	f[3] = get_quotes;
	while (++i < (int)ft_strlen(spec))
	{
		if (all->line[all->pos] == spec[i])
		{
			if (f[i](all, text) == -1)
				return (-1);
			return (1);
		}
	}
	return (0);
}

/*
** Checks for special characters
**
** @param *all general structure
** @param **spec array of special characters
** @param max the number of elements in the array **spec
** @return 1 if it finds a special character from the array, otherwise 0
*/

int			is_spec(t_all *all, const char **spec, int max)
{
	int		i;

	i = -1;
	while (++i < max)
	{
		if (!ft_strncmp(&all->line[all->pos], spec[i], ft_strlen(spec[i])))
			return (1);
	}
	return (0);
}
