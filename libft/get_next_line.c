/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 14:01:03 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/12 10:49:18 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int		set_read(int fd, char **line)
{
	char	*res;
	int		red;
	char	buf[2];

	while ((red = read(fd, buf, 1)) > 0)
	{
		buf[1] = 0;
		if (buf[0] == '\n')
			break ;
		if (!*line)
		{
			if (!(*line = ft_strdup("")))
				return (-1);
		}
		res = *line;
		if (!(*line = ft_strjoin(res, buf)))
			return (-1);
		free(res);
	}
	return (red);
}

int				get_next_line(int fd, char **line)
{
	if (fd < 0 || !line)
		return (-1);
	return (set_read(fd, line));
}
