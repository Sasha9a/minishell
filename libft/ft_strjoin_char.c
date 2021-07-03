/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:10:56 by jlyessa           #+#    #+#             */
/*   Updated: 2021/03/02 14:18:11 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char c)
{
	char	*res;
	int		i;

	if (!c)
		return (NULL);
	if (s1)
	{
		i = ft_strlen((char*)s1) + 2;
		if (!(res = malloc(sizeof(char) * i)))
			return (NULL);
		ft_strlcpy(res, (char *)s1, ft_strlen((char *)s1) + 1);
	}
	else
	{
		i = 2;
		if (!(res = malloc(sizeof(char) * i)))
			return (NULL);
	}
	res[i - 2] = c;
	res[i - 1] = '\0';
	return (res);
}
