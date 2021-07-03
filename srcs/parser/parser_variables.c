/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 00:04:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/14 10:58:16 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_loc(char **text)
{
	if (*text)
		free(*text);
	return (-1);
}

static int	is_cmd_export(t_all *all, char **text)
{
	if (!ft_strncmp(((t_cmd*)ft_lstlast(all->cmd)->content)->name, "export", 7))
	{
		if (join_char(text, all->line[all->pos]) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

/*
** display the result of the last operation
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 1 if there was $?, If not 0, error -1
*/

static int	get_result(t_all *all, char **text)
{
	char	*num;

	if (all->line[all->pos] == '?')
	{
		if (!(num = ft_itoa(all->res)))
			return (-1);
		if (join_str(text, num) == -1)
			return (-1);
		free(num);
		all->pos++;
		return (1);
	}
	return (0);
}

/*
** Replaces text with the value of an environment variable
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @param *var environment variable name
** @return 0 if good, otherwise -1
*/

static int	set_env(t_all *all, char **text, char *var)
{
	t_list		*lst;

	lst = all->env;
	while (lst)
	{
		if (!ft_strncmp(var, ((t_env*)lst->content)->name, ft_strlen(var) + 1))
		{
			if (join_str(text, ((t_env*)lst->content)->par) == -1)
				return (-1);
			break ;
		}
		lst = lst->next;
	}
	return (0);
}

/*
** Replaces text with the value of an environment variable
**
** @param *all general structure
** @param **text pointer to the string to which the result is written
** @return 0 if good, otherwise -1
*/

int			get_variables(t_all *all, char **text)
{
	char		*var;
	const char	spec[11] = " \'\";|><$?:";
	int			res;
	int			export;

	if ((export = is_cmd_export(all, text)) == -1)
		return (-1);
	all->pos++;
	var = NULL;
	if ((res = get_result(all, text)) == -1)
		return (-1);
	if (!res && !export)
	{
		while (all->line[all->pos] && !ft_strchr(spec, all->line[all->pos]))
		{
			if (join_char(&var, all->line[all->pos]) == -1)
				return (free_loc(&var));
			all->pos++;
		}
		if (set_env(all, text, var) == -1)
			return (free_loc(&var));
	}
	free(var);
	return (0);
}
