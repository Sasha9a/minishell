/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:49:01 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:17:07 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clears the entire list of environment variable
**
** @param **lst pointer to list of environment variables
*/

void		clear_env(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		free(((t_env*)(*lst)->content)->name);
		if (((t_env*)(*lst)->content)->par)
			free(((t_env*)(*lst)->content)->par);
		tmp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(tmp, free);
	}
	*lst = NULL;
}

/*
** Clears 1 item of an environment variable
**
** @param **tmp pointer to environment variable
** @param **lst pointer to environment variable list
** @return -1
*/

int			free_env(t_env **tmp, t_list **lst)
{
	if (*tmp)
	{
		free((*tmp)->name);
		if ((*tmp)->par)
			free((*tmp)->par);
		free(*tmp);
	}
	if (*lst)
		free(*lst);
	return (-1);
}

/*
** updates the environment variable.
** If the environment variable is not found in the sheet, then,
** if necessary, it creates it
**
** @param *all general structure
** @param *name environment variable name
** @param *txt new environment variable value
** @param is_created if the value is 1, then it creates it, if not found
** @return 0 if good, otherwise -1
*/

int			update_env(t_all *all, char *name, char *txt, char is_created)
{
	t_list	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env*)tmp->content)->name, name,
			ft_strlen(name) + 1))
		{
			if (((t_env*)tmp->content)->par)
				free(((t_env*)tmp->content)->par);
			if (!(((t_env*)tmp->content)->par = ft_strdup(txt)))
				return (-1);
			return (0);
		}
		tmp = tmp->next;
	}
	if (is_created == 1)
	{
		if (add_env(all, ft_strdup(name), ft_strdup(txt)) == -1)
			return (-1);
		all->env = sort_env(all->env);
	}
	return (0);
}

/*
** additional function for sorting. It changes pointers of lists
**
** @param *res summary list pointer
** @param *tmp temporary variable, helps to change pointers
*/

static void	sort_env1(t_list *res, t_list *tmp)
{
	t_list	*current;

	current = res;
	while (current->next && ft_strncmp(((t_env*)tmp->content)->name,
	((t_env*)current->next->content)->name,
	ft_strlen(((t_env*)tmp->content)->name) + 1) >= 0)
		current = current->next;
	tmp->next = current->next;
	current->next = tmp;
}

/*
** sorts the list of environment variables
**
** @param *lst list of environment variables
** @return pointer to updated list, NULL if sheet is empty
*/

t_list		*sort_env(t_list *lst)
{
	t_list	*res;
	t_list	*tmp;

	res = NULL;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (!res || ft_strncmp(((t_env*)tmp->content)->name,
		((t_env*)res->content)->name,
		ft_strlen(((t_env*)tmp->content)->name) + 1) < 0)
		{
			tmp->next = res;
			res = tmp;
		}
		else
			sort_env1(res, tmp);
	}
	return (res);
}
