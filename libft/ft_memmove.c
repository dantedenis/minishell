/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:15:24 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:17:24 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*pdst;
	char	*psrc;

	pdst = (char *) dst;
	psrc = (char *) src;
	if (src < dst && src + len > dst)
		while (len-- >= 1)
			pdst[len] = psrc[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
