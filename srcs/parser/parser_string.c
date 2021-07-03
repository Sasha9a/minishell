/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:03:16 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:16:03 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** gets the name of the command entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

static int	get_name(t_all *all)
{
	const char	*spec[6] = { " ", "|", ";", "<", ">>", ">" };

	while (all->line[all->pos])
	{
		if (is_spec(all, spec, 6))
			return (0);
		if (!get_spec(all, &((t_cmd*)ft_lstlast(all->cmd)->content)->name))
		{
			if (join_char(&((t_cmd*)ft_lstlast(all->cmd)->content)->name,
				all->line[all->pos]) == -1)
				return (-1);
			all->pos++;
		}
	}
	return (0);
}

/*
** function continuation get_arg
**
** @param *all general structure
** @param i the current index of the command argument
** @return 0 if good, otherwise -1
*/

static int	get_arg2(t_all *all, int i)
{
	if (!get_spec(all, &((t_cmd*)ft_lstlast(all->cmd)->content)->argv[i]))
	{
		if (join_char(&((t_cmd*)ft_lstlast(all->cmd)->content)->argv[i],
			all->line[all->pos]) == -1)
			return (-1);
		all->pos++;
	}
	return (0);
}

/*
** gets all the arguments entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

static int	get_arg(t_all *all)
{
	int			i;
	const char	*spec[3] = { "<", ">>", ">" };

	i = 0;
	while (all->line[all->pos] && !ft_strchr(";|", all->line[all->pos]))
	{
		if (is_spec(all, spec, 3))
		{
			if (parser_redir(all) == -1)
				return (-1);
			continue ;
		}
		if (all->line[all->pos] == ' ')
		{
			if (add_remalloc_argv(all, &i) == -1)
				return (-1);
		}
		else
		{
			if (get_arg2(all, i) == -1)
				return (-1);
		}
	}
	return (0);
}

/*
** Parses the string entered by the user
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

int			parser_string(t_all *all)
{
	t_list		*lst;

	if (!(lst = init_cmd()))
		return (-1);
	ft_lstadd_back(&all->cmd, lst);
	trim_space(all);
	if (get_name(all) == -1)
		return (-1);
	trim_space(all);
	if (get_arg(all) == -1)
		return (-1);
	if (all->line[all->pos] == '|')
		((t_cmd*)ft_lstlast(all->cmd)->content)->pipe = 1;
	if (ft_strchr("|;", all->line[all->pos]))
		all->pos++;
	return (0);
}
