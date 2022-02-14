/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:41:50 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:41:50 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*temp;

	temp = (char *)str;
	while (*temp != (unsigned char)ch)
	{
		if (*temp == 0)
			return (NULL);
		++temp;
	}
	return (temp);
}
