/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:22:09 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:22:13 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ret = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		ret[i] = *s1;
		++s1;
		++i;
	}
	while (*s2)
	{
		ret[i] = *s2;
		++s2;
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
