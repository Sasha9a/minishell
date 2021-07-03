/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:13:56 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:29:38 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	i = 0;
	res = (unsigned char *)s1;
	res1 = (unsigned char *)s2;
	while ((res[i] || res1[i]) && n > i)
	{
		if (res[i] != res1[i])
			return (res[i] - res1[i]);
		i++;
	}
	return (0);
}
