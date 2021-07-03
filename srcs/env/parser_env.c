/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:49:31 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 16:57:19 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get environment variable name from string
**
** @param *env the line where you need to get the name
** @return pointer to name, otherwise NULL
*/

char	*get_name_env(char *env)
{
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

/*
** get environment variable value from string
**
** @param *env the line where you need to get the value
** @return pointer to value, otherwise NULL
*/

char	*get_param_env(char *env)
{
	int		i;
	int		size;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i])
		i++;
	size = 0;
	while (env[i + size])
		size++;
	return (ft_substr(env, i, size));
}

/*
** looks for an environment variable by its name
**
** @param *all general structure
** @param *name environment variable name
** @return pointer to an environment variable, otherwise NULL
*/

t_env	*get_env(t_all *all, char *name)
{
	t_list	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env*)tmp->content)->name, name,
			ft_strlen(name) + 1))
			return ((t_env*)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** add environment variable
**
** @param *all general structure
** @param *name environment variable name
** @param *par environment variable parameter
** @return 0 if good, otherwise -1
*/

int		add_env(t_all *all, char *name, char *par)
{
	t_env	*tmp;
	t_list	*lst;

	lst = NULL;
	if (!(tmp = malloc(sizeof(t_env))) ||
		!(tmp->name = name))
	{
		if (name)
			free(name);
		return (free_env(&tmp, &lst));
	}
	tmp->par = par;
	if (!(lst = ft_lstnew(tmp)))
	{
		free(name);
		return (free_env(&tmp, &lst));
	}
	ft_lstadd_back(&all->env, lst);
	return (0);
}

/*
** parses environment variables into t_list
**
** @param *all general structure
** @param **env environment variables
** @return 0 if good, otherwise -1
*/

int		parser_env(t_all *all, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (add_env(all, get_name_env(env[i]), get_param_env(env[i])) == -1)
			return (-1);
	}
	return (0);
}
