/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:53:48 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:53:48 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	int		result;

	if (!*little)
		return ((char *)big);
	len_little = ft_strlen(little);
	result = 1;
	while (result && *big && (len-- >= len_little))
	{
		result = ft_strncmp(big, little, len_little);
		++big;
	}
	if (result)
		return (NULL);
	return ((char *)(big - 1));
}
