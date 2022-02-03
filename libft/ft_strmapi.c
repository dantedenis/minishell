/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:52:50 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:52:50 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	index;

	if (!s || !f)
		return (NULL);
	result = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (NULL);
	index = -1;
	while (s[++index])
		result[index] = f(index, s[index]);
	result[index] = 0;
	return (result);
}
