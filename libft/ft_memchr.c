/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:28:06 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:28:06 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	if (n)
	{
		ptr = (const unsigned char *)s;
		while (n--)
		{
			if (*ptr++ == (unsigned char)c)
				return ((void *)(ptr - 1));
		}	
	}
	return (NULL);
}
