/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:18:37 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:18:57 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_strlen(s1) + 1);
	if (dup == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}
