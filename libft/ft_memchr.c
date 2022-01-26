/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:13:50 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:17:44 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *) s;
	while (i < n)
	{
		if (c == p[i])
			return ((void *) s + i);
		++i;
	}
	return ((void *) 0);
}
