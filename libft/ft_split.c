/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:36:31 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/16 17:17:00 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countstr(char const *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++ret;
		while (*s && *s != c)
			++s;
	}
	return (ret);
}

static size_t	ft_substrlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		++i;
	return (i);
}

static char	*ft_substrdup(char const *s, char c)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_substrlen(s, c) + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != c && s[i])
	{
		dup[i] = s[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	i;

	if (s == NULL)
		return (NULL);
	ret = (char **) malloc((ft_countstr(s, c) + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
		{
			ret[i] = ft_substrdup(s, c);
			if (ret[i] == NULL)
				return (ft_freearr(&ret));
			++i;
		}
		while (*s && *s != c)
			++s;
	}
	ret[i] = NULL;
	return (ret);
}
