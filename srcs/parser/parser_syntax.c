/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:42:25 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/14 11:45:36 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** displays an error
**
** @param *all general structure
** @param *text error text
** @return -1
*/

static int	ret_err(t_all *all, char *text)
{
	all->res = 2;
	return (ft_error(NULL, text, -1));
}

static void	trim_quotes(t_all *all, int *i, char c)
{
	if (ft_strchr("\'\"", all->line[*i]))
	{
		if (i && all->line[*i - 1] == '\\')
			return ;
		while (all->line[++(*i)])
		{
			if (all->line[*i] == c)
			{
				if (*i && all->line[*i - 1] == '\\')
					continue ;
				break ;
			}
		}
	}
}

static int	is_norm_separator(t_all *all)
{
	int		i;
	int		ch;
	int		is;

	i = -1;
	ch = 0;
	is = 0;
	while (all->line[++i])
	{
		if (ft_strchr("|;", all->line[i]))
		{
			is = (all->line[i] == ';') ? -1 : -2;
			if (!ch)
				return (is);
			ch = 0;
			continue ;
		}
		if (all->line[i] != ' ')
			ch = 1;
		trim_quotes(all, &i, all->line[i]);
	}
	if (is == -2 && !ch)
		return (is);
	return (1);
}

int			parser_syntax(t_all *all)
{
	int		ret_quotes;
	int		ret_separator;

	if (!is_norm_shielding(all))
		return (ret_err(all, "syntax error \"\\\""));
	ret_quotes = is_norm_quotes(all);
	if (!ret_quotes)
		return (ret_err(all, "syntax error \"\'\""));
	if (ret_quotes == -1)
		return (ret_err(all, "syntax error \"\"\""));
	ret_separator = is_norm_separator(all);
	if (ret_separator == -1)
		return (ret_err(all, "syntax error \";\""));
	if (ret_separator == -2)
		return (ret_err(all, "syntax error \"|\""));
	return (0);
}
