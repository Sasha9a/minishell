/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchicken <tchicken@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:28:47 by tchicken          #+#    #+#             */
/*   Updated: 2021/03/11 15:28:53 by tchicken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			strs_size(char **strs)
{
	int res;

	res = 0;
	while (*strs)
	{
		res++;
		strs++;
	}
	return (res);
}
