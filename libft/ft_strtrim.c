/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:25:26 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:25:28 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charinset(char ch, char const *set)
{
	while (*set)
	{
		if (ch == *set)
			return (1);
		++set;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0')
		return ((char *) s1);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (ft_charinset(s1[begin], set))
		++begin;
	if (begin != end + 1)
		while (ft_charinset(s1[end], set))
			--end;
	return (ft_substr(s1, begin, end - begin + 1));
}
