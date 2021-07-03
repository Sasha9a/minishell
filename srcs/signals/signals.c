/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:25:23 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/17 21:58:30 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "libft.h"

void	handle_sigint(int sigcode)
{
	(void)sigcode;
	ft_putstr_fd("\n", 1);
	*g_state.exit_code = 130;
	if (!g_state.cmdrun)
	{
		if (*g_state.line)
		{
			free(*g_state.line);
			*g_state.line = NULL;
		}
		ft_putstr_fd("bash-3.2$ ", 1);
	}
}

void	handle_sigquit(int sigcode)
{
	(void)sigcode;
	if (!g_state.cmdrun)
		ft_putstr_fd("\b\b  \b\b", 1);
	else
		ft_putendl_fd("Quit (core dumped)", 1);
}

void	set_signals(void)
{
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
