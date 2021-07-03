/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:52:39 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:26:39 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*res1;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	res = dest;
	res1 = (unsigned char *)src;
	if (res < res1)
		while (n--)
			*(res++) = *(res1++);
	else
		while (n > i++)
			res[n - i] = res1[n - i];
	return (dest);
}
