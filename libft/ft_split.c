/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:36:31 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:36:34 by lcoreen          ###   ########.fr       */
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

static char	**ft_freearr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	return (NULL);
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
				return (ft_freearr(ret, i));
			++i;
		}
		while (*s && *s != c)
			++s;
	}
	ret[i] = NULL;
	return (ret);
}
