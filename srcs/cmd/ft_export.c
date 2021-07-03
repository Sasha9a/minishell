/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 10:35:39 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/14 11:21:23 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_loc(char **name, char **par)
{
	if (*name)
		free(*name);
	if (*par)
		free(*par);
	return (-1);
}

/*
** displays a complete list of all environment variables
**
** @param *all general structure
*/

static void	show_all_env(t_all *all)
{
	t_list	*lst;

	lst = all->env;
	while (lst)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_env*)lst->content)->name, 1);
		if (((t_env*)lst->content)->par)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_env*)lst->content)->par, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}

/*
** re-updates the value of an environment variable
**
** @param *all general structure
** @param *text export command argument
** @return 0 if good, otherwise -1
*/

static int	update_env_local(t_all *all, char *text)
{
	char	*name;
	char	*par;
	t_env	*tmp;

	if (!(name = get_name_env(text))
		|| !(par = get_param_env(text)))
		return (free_loc(&name, &par));
	if (!(tmp = get_env(all, name)))
	{
		if (add_env(all, name, par) == -1)
			return (free_loc(&name, &par));
	}
	else
	{
		if (tmp->par)
			free(tmp->par);
		tmp->par = par;
		free(name);
	}
	return (0);
}

/*
** makes a check that the name of the environment variable is valid
**
** @param *text export command argument
** @return 1 is valid, otherwise 0
*/

static int	is_valid_argv(char *text)
{
	int		i;

	i = 0;
	while (text[i] && text[i] != '=')
	{
		if (!((text[i] >= 'a' && text[i] <= 'z') ||
			(text[i] >= 'A' && text[i] <= 'Z') || text[i] == '_' ||
			(i && (text[i] >= '0' && text[i] <= '9'))))
		{
			ft_putstr_fd("export: \"", 2);
			ft_putstr_fd(text, 2);
			ft_putstr_fd("\" this is an invalid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** executes the export command
**
** @param *all general structure
** @param *cmd command structure
** @return 0 if good, otherwise -1
*/

int			ft_export(t_all *all, t_cmd *cmd)
{
	int		i;

	i = -1;
	all->res = 0;
	if (!ft_strncmp(cmd->argv[0], "", 1))
		show_all_env(all);
	else
	{
		while (cmd->argv[++i])
		{
			if (is_valid_argv(cmd->argv[i]))
			{
				if (update_env_local(all, cmd->argv[i]) == -1)
					return (-1);
				all->env = sort_env(all->env);
			}
			else
				all->res = 1;
		}
	}
	return (0);
}
