/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:28:23 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:28:25 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*elem;

	if (lst != NULL)
	{
		ret = ft_lstnew((*f)(lst->content));
		if (ret == NULL)
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			elem = ft_lstnew((*f)(lst->content));
			if (elem == NULL)
			{
				ft_lstclear(&ret, del);
				return (NULL);
			}
			ft_lstadd_back(&ret, elem);
			lst = lst->next;
		}
		return (ret);
	}
	else
		return (NULL);
}
