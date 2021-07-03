/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:05:41 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/17 21:55:57 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft.h"

typedef struct	s_state
{
	char	**line;
	int		*exit_code;
	int		cmdrun;
}				t_state;

extern t_state	g_state;

typedef struct	s_env
{
	char	*name;
	char	*par;
}				t_env;

typedef struct	s_redir
{
	char *name;
	char type;
}				t_redir;

typedef struct	s_cmd
{
	char	*name;
	char	**argv;
	char	pipe;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		error;
	t_list	*redirs;
}				t_cmd;

typedef struct	s_all
{
	t_list	*env;
	t_list	*cmd;
	char	*line;
	int		pos;
	int		res;
}				t_all;

int				parser_env(t_all *all, char **env);
t_env			*get_env(t_all *all, char *name);
char			*get_name_env(char *env);
char			*get_param_env(char *env);
int				add_env(t_all *all, char *name, char *par);
int				update_env(t_all *all, char *name, char *txt, char is_created);
t_list			*sort_env(t_list *lst);
int				free_env(t_env **tmp, t_list **lst);
void			clear_env(t_list **lst);
int				clear_all(t_all *all);
void			clear(t_all *all);
char			**convert_env(t_all *all);
char			**convert_argv(t_list *lst);
char			*get_full_cmd_name(t_all *all, t_list *lst);

int				parser_string(t_all *all);
int				get_shielding(t_all *all, char **text);
int				is_norm_shielding(t_all *all);
int				get_variables(t_all *all, char **text);
int				get_strong_quotes(t_all *all, char **text);
int				get_quotes(t_all *all, char **text);
int				is_norm_quotes(t_all *all);
int				parser_cmd(t_all *all);
int				parser_syntax(t_all *all);
int				parser_redir(t_all *all);
int				is_spec(t_all *all, const char **spec, int max);
int				get_spec(t_all *all, char **text);

int				ft_echo(t_all *all, t_cmd *cmd);
int				ft_pwd(t_all *all, t_cmd *cmd);
int				ft_export(t_all *all, t_cmd *cmd);
int				ft_env(t_all *all, t_cmd *cmd);
int				ft_unset(t_all *all, t_cmd *cmd);
int				ft_cd(t_all *all, t_cmd *cmd);
int				ft_exit(t_all *all, t_cmd *cmd);

t_list			*init_cmd(void);
t_list			*init_redir(void);
void			clear_cmd(t_list **lst);

int				join_char(char **text, char c);
int				join_str(char **text, char *s);
void			trim_space(t_all *all);
char			**remalloc_args(char **args);
int				add_remalloc_argv(t_all *all, int *i);
void			*free_split(char **text);

int				ft_error(char *name, char *text, int ret);

int				run_pipe(t_list *cmds, t_all *all);
int				handle_redir(t_list *elems);
int				bash_err(char *str1, char *str2, int ret);
t_cmd			*ltoc(t_list *lst);
t_redir			*ltor(t_list *lst);

int				start_cmd(t_all *all, t_list *lst);
int				free_local(char **split, char **split2, char **text, int ret);

int				fd_init(t_list *cmd);
int				fd_restore(t_list *cmd);

void			set_signals(void);
void			free_t_env(void *data);

int				strs_size(char **strs);
int				remove_env(t_list **env, char *name);
void			child_proc(int *pipefd, int prev_pipefd0,
							t_list *cmd, t_all *all);

#endif
