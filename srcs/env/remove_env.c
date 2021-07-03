/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:37:31 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/12 13:30:47 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			remove_env(t_list **env, char *name)
{
	t_list *prev;
	t_list *now;

	now = *env;
	prev = *env;
	while (now)
	{
		if (!ft_strncmp(((t_env *)now->content)->name,
							name, ft_strlen(name) + 1))
		{
			prev->next = now->next;
			ft_lstdelone(now, free_t_env);
			if (*env == now)
				*env = now->next;
			return (1);
		}
		prev = now;
		now = now->next;
	}
	return (0);
}

void		free_t_env(void *data)
{
	t_env *env;

	env = (t_env *)data;
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->par)
			free(env->par);
		free(env);
	}
}
