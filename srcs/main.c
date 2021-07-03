/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:08:51 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/17 21:58:58 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

t_state		g_state = {NULL, NULL, 0};

/*
** Updates all parameters of the t_all structure to the standard
** ones to get a new line from the user
**
** @param *all general structure
*/

static void	update_main(t_all *all)
{
	clear_cmd(&all->cmd);
	free(all->line);
	all->line = NULL;
	all->pos = 0;
}

/*
** Start parsing the entered data
**
** @param *all general structure
*/

static int	parse_line(t_all *all)
{
	if (all->line && !parser_syntax(all))
	{
		while (all->line[all->pos])
		{
			if (parser_string(all) == -1)
				return (-1);
			if (!handle_redir(ft_lstlast(all->cmd)))
				ltoc(ft_lstlast(all->cmd))->error = 1;
			if (!((t_cmd*)ft_lstlast(all->cmd)->content)->pipe)
			{
				if (parser_cmd(all) == -1)
					return (-1);
				clear_cmd(&all->cmd);
			}
		}
	}
	return (0);
}

static int	handle_args(t_all *all, char *str)
{
	all->line = ft_strdup(str);
	if (parse_line(all) == -1)
		return (clear_all(all));
	update_main(all);
	clear_all(all);
	return (all->res);
}

static void	read_cycle(t_all *all)
{
	int gnl;

	while ((gnl = get_next_line(0, &all->line)) >= 0)
	{
		if (!gnl)
		{
			if (!all->line || !ft_strlen(all->line))
			{
				ft_putendl_fd("exit", 1);
				break ;
			}
			continue ;
		}
		if (parse_line(all) == -1)
			return ;
		update_main(all);
		ft_putstr_fd("bash-3.2$ ", 1);
	}
	if (gnl == -1)
		bash_err("read", strerror(errno), 0);
}

/*
** Main function
**
** @param args number of arguments
** @param **argv arguments
** @param **env environment variables
** @return 0 if good, otherwise -1
*/

int			main(int args, char **argv, char **env)
{
	t_all	all;

	set_signals();
	clear(&all);
	g_state.line = &all.line;
	g_state.exit_code = &all.res;
	parser_env(&all, env);
	remove_env(&all.env, "OLDPWD");
	remove_env(&all.env, "PWD");
	add_env(&all, ft_strdup("PWD"), getcwd(NULL, 0));
	if (args == 3 && !ft_strncmp("-c", argv[1], 3))
		return (handle_args(&all, argv[2]));
	else if (args != 1)
	{
		bash_err("unsupported arguments", NULL, 0);
		clear_all(&all);
		return (1);
	}
	ft_putstr_fd("bash-3.2$ ", 1);
	read_cycle(&all);
	clear_all(&all);
	return (all.res);
}
