/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:33:46 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:33:46 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	ret = (char *) malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		ret[i] = s[start + i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
