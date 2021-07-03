/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyessa <jlyessa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:21:04 by jlyessa           #+#    #+#             */
/*   Updated: 2020/12/03 21:25:15 by jlyessa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*i;

	if (!lst || !f || !del)
		return (NULL);
	if (!(i = ft_lstnew(f(lst->content))))
		return (NULL);
	res = i;
	lst = lst->next;
	while (lst)
	{
		if (!(i = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, i);
		lst = lst->next;
	}
	return (res);
}
