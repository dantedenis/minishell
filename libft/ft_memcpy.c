/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:15:08 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:17:32 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*pdst;
	char	*psrc;

	if (!dst && !src)
		return (dst);
	i = 0;
	pdst = (char *) dst;
	psrc = (char *) src;
	while (i < n)
	{
		pdst[i] = psrc[i];
		++i;
	}
	return (dst);
}
