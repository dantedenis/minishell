/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:42:30 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:42:30 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	void	*dest;

	size = ft_strlen(s) + 1;
	dest = ft_calloc(size, sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_memcpy(dest, s, size));
}
