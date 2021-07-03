/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:39:57 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:41:00 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_redir(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		free(((t_redir*)tmp->content)->name);
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
}

/*
** Clears the entire t_cmd structure
**
** @param **lst Pointer to sheet of structure t_cmd
*/

void		clear_cmd(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = -1;
		free(((t_cmd*)tmp->content)->name);
		if (((t_cmd*)tmp->content)->argv)
		{
			while (((t_cmd*)tmp->content)->argv[++i])
				free(((t_cmd*)tmp->content)->argv[i]);
		}
		free(((t_cmd*)tmp->content)->argv);
		clear_redir(&((t_cmd*)tmp->content)->redirs);
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
}

/*
** Clears the entire t_all structure
**
** @param *all general structure
*/

int			clear_all(t_all *all)
{
	clear_cmd(&all->cmd);
	clear_env(&all->env);
	free(all->line);
	all->line = NULL;
	return (-1);
}

/*
** Clears an array of strings
**
** @param **text Pointer to array of strings
*/

void		*free_split(char **text)
{
	int		i;

	i = -1;
	if (text)
	{
		while (text[++i])
			free(text[i]);
		free(text);
	}
	return (NULL);
}

/*
** Zeroes all parameters in the structure t_all
**
** @param *all general structure
*/

void		clear(t_all *all)
{
	all->env = NULL;
	all->cmd = NULL;
	all->line = NULL;
	all->pos = 0;
	all->res = 0;
}
