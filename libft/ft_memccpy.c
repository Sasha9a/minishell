/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:33:36 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:25:57 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	i = 0;
	res = dest;
	res1 = (unsigned char *)src;
	while (i < n)
	{
		res[i] = res1[i];
		if (res[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
