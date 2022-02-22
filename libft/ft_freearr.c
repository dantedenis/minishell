/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:41:46 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/21 19:44:25 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freearr(char ***arr)
{
	size_t	i;
	char	**temp;

	i = 0;
	temp = *arr;
	while (temp[i] != NULL)
	{
		free(temp[i]);
		++i;
	}
	free(temp);
	*arr = NULL;
	return (NULL);
}
