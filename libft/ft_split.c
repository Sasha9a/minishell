/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:07:05 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:27:54 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_worlds(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (*s)
	{
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			res++;
		}
		s++;
	}
	return (res);
}

static int	num_world(char const *s, char c, int i)
{
	int	res;

	res = 0;
	while (s[i] != c && s[i])
	{
		res++;
		i++;
	}
	return (res);
}

static char	**err(char **res, int j)
{
	while (j)
	{
		j--;
		free((void *)res[j]);
	}
	free(res);
	return (NULL);
}

static char	**set_worlds(char **res, char const *s, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && l > j)
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!(res[j] = ft_calloc(num_world(s, c, i) + 1, sizeof(char))))
			return (err(res, j));
		while (s[i] && s[i] != c)
			res[j][k++] = s[i++];
		res[j][k] = '\0';
		j++;
	}
	res[j] = 0;
	return (res);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	i = num_worlds(s, c);
	if (!(res = ft_calloc(i + 1, sizeof(char*))))
		return (NULL);
	return (set_worlds(res, s, c, i));
}
