/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 20:22:04 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 20:22:04 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*beg;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	beg = ft_lstnew(f(lst->content));
	temp = beg;
	while (lst->next)
	{
		lst = lst->next;
		temp->next = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&beg, del);
			return (NULL);
		}
		temp = temp->next;
	}
	return (beg);
}
