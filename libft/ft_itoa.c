/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:40:08 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:21:48 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(int n)
{
	int		res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		res++;
	}
	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

char			*ft_itoa(int n)
{
	int		i;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = len(n);
	if (!(res = ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	res[i--] = '\0';
	if (n == 0)
		res[0] = '0';
	else
	{
		if (n < 0)
		{
			res[0] = '-';
			n *= -1;
		}
		while (n != 0)
		{
			res[i--] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (res);
}
