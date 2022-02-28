/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:31:40 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 20:52:50 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	print_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	print_list(t_list *lst, char *lstname)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s %d: %s\n", lstname, i, (char *)lst->content);
		lst = lst->next;
		++i;
	}
}
