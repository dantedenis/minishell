/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:27:25 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:39:26 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*begin;

	begin = *lst;
	while (begin)
	{
		next = begin->next;
		(*del)(begin->content);
		free(begin);
		begin = next;
	}
	*lst = 0;
}
