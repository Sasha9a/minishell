/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:23:43 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:26:30 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*res1;

	if (n == 0 || dest == src)
		return (dest);
	res = dest;
	res1 = (unsigned char *)src;
	while (n > 0)
	{
		res[n - 1] = res1[n - 1];
		n--;
	}
	return (dest);
}
