/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:35:55 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:35:55 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*from;
	unsigned char	*to;
	int				i;

	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	if (from == to || n == 0)
		return (dest);
	if (to > from && (to - from) < (int)n)
	{
		i = n;
		while (--i >= 0)
			to[i] = from[i];
		return (dest);
	}
	if (from > to && (from - to) < (int)n)
	{
		i = -1;
		while (++i < (int)n)
			to[i] = from[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
