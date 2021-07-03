/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:34:13 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/12 12:15:16 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>

int		fd_init(t_list *cmd)
{
	int fd_in;
	int fd_out;

	if (ltoc(cmd)->fd_in != -1)
	{
		if ((fd_in = dup(0)) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		if (dup2(ltoc(cmd)->fd_in, 0) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		ltoc(cmd)->fd_in = fd_in;
	}
	if (ltoc(cmd)->fd_out != -1)
	{
		if ((fd_out = dup(1)) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		if (dup2(ltoc(cmd)->fd_out, 1) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		ltoc(cmd)->fd_out = fd_out;
	}
	return (1);
}

int		fd_restore(t_list *cmd)
{
	int fd_in;
	int fd_out;

	if (ltoc(cmd)->fd_in != -1)
	{
		if ((fd_in = dup(0)) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		if (dup2(ltoc(cmd)->fd_in, 0) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		ltoc(cmd)->fd_in = fd_in;
	}
	if (ltoc(cmd)->fd_out != -1)
	{
		if ((fd_out = dup(1)) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		if (dup2(ltoc(cmd)->fd_out, 1) == -1)
			return (bash_err(ltoc(cmd)->name, strerror(errno), 0));
		ltoc(cmd)->fd_out = fd_out;
	}
	return (1);
}
