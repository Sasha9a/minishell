/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 21:20:05 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 12:15:33 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** function pointers initialization
**
** @param **f a pointer to an array of functions
*/

static void	init_f(int (**f)(t_all*, t_cmd*))
{
	f[0] = ft_echo;
	f[1] = ft_pwd;
	f[2] = ft_export;
	f[3] = ft_env;
	f[4] = ft_unset;
	f[5] = ft_cd;
	f[6] = ft_exit;
}

/*
** launching its functions
**
** @param *all general structure
** @param *lst command pointer
** @return 1 if the command is executed, 0 if not executed, the error is -1
*/

int			start_cmd(t_all *all, t_list *lst)
{
	int			i;
	const char	*name[7] = { "echo", "pwd", "export", "env", "unset", "cd",
				"exit" };
	int			(*f[7])(t_all*, t_cmd*);

	i = 0;
	init_f(f);
	while (i < 7)
	{
		if (!ft_strncmp(((t_cmd*)lst->content)->name, name[i],
			ft_strlen(name[i]) + 1))
		{
			if (f[i](all, (t_cmd*)lst->content) == -1)
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** clears strings
**
** @param **split array of strings
** @param **split2 array of strings
** @param **text pointer to string
** @param ret return
** @return ret
*/

int			free_local(char **split, char **split2, char **text, int ret)
{
	if (split)
		free_split(split);
	if (split2)
		free_split(split2);
	if (*text)
		free(*text);
	return (ret);
}

/*
** execute the command
**
** @param *all general structure
** @return 0 if good, otherwise -1
*/

static int	set_underscore(t_all *all, t_cmd *cmd)
{
	char	*arg;
	int		argv_size;

	argv_size = strs_size(cmd->argv);
	if (argv_size == 1 && !ft_strncmp(cmd->argv[0], "", 1))
		arg = cmd->name;
	else
		arg = cmd->argv[argv_size - 1];
	return (update_env(all, "_", arg, 1));
}

int			parser_cmd(t_all *all)
{
	t_list	*lst;
	int		res_cmd;

	lst = all->cmd;
	if (ft_lstsize(lst) == 1)
	{
		if (!fd_init(lst) ||
			(res_cmd = start_cmd(all, lst)) == -1 ||
			!fd_restore(lst))
			return (-1);
		if (!res_cmd)
		{
			if ((all->res = run_pipe(lst, all)) == -1)
				return (-1);
		}
	}
	else
	{
		if ((all->res = run_pipe(lst, all)) == -1)
			return (-1);
	}
	if (lst && lst->content
	&& set_underscore(all, ft_lstlast(lst)->content) == -1)
		return (-1);
	return (0);
}
