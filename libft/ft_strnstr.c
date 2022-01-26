/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:26:14 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:26:16 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	if (*needle == '\0')
		return ((char *) haystack);
	n = 0;
	while (haystack[n] && n < len)
	{
		i = 0;
		while (haystack[n + i] == needle[i] && n + i < len)
		{
			++i;
			if (needle[i] == '\0')
				return ((char *)(haystack + n));
		}
		++n;
	}
	return ((char *) 0);
}
