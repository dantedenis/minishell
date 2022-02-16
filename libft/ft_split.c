/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:41:35 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/16 17:37:13 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_count(const char *str, char ch)
{
	int	i;
	int	words;

	words = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i + 1] == ch || !str[i + 1]) && !(str[i] == ch || !str[i]))
			words++;
	}
	return (words);
}

static void	word_copy(char *dest, const char *src, char ch)
{
	while (*src && *src != ch)
		*dest++ = *src++;
	*dest = 0;
}

static short	delete_words(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (1);
}

static short	to_fill(char **words, const char *str, char ch)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch || !str[i])
			++i;
		else
		{
			j = 0;
			while (str[i + j] != ch && str[i + j])
				++j;
			words[index] = ft_calloc(j + 1, sizeof(char));
			if (!words[index])
				return (delete_words(words, index - 1));
			word_copy(words[index], str + i, ch);
			i += j;
			++index;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = to_count(s, c);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	result[words] = 0;
	if (to_fill(result, s, c))
		return (NULL);
	return (result);
}
