/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:41:46 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/16 17:17:49 by lcoreen          ###   ########.fr       */
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
