/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:09:53 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/11 18:09:53 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ch;
	size_t	i;

	ch = NULL;
	if (!c)
		return ((char *)str + ft_strlen(str));
	i = -1;
	while (str[++i])
		if (str[i] == (unsigned char)c)
			ch = (char *)(str + i);
	return (ch);
}
