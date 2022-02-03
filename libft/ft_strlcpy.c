/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:51:32 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:51:32 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *str, size_t size)
{
	size_t	strlen;

	strlen = ft_strlen(str);
	if (strlen + 1 < size)
		ft_memcpy(dest, str, strlen + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, str, size - 1);
		dest[size - 1] = '\0';
	}
	return (strlen);
}
