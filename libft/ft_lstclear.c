/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:57:18 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 19:57:18 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*del_lst;

	temp = *lst;
	while (temp)
	{
		del_lst = temp;
		temp = temp->next;
		ft_lstdelone(del_lst, del);
	}
	*lst = NULL;
}
