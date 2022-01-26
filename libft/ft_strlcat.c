/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:25:45 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:25:47 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(dst);
	i = 0;
	while (i + 1 + len < dstsize && src[i])
	{
		dst[i + len] = src[i];
		++i;
	}
	if (dstsize > len)
		dst[i + len] = '\0';
	if (len > dstsize)
		return (dstsize + ft_strlen(src));
	return (len + ft_strlen(src));
}
