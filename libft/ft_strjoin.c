/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 09:24:30 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:28:43 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1;
	if (!(res = malloc(sizeof(char) * i)))
		return (NULL);
	ft_strlcpy(res, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(res, s2, i);
	return (res);
}
