/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:22:57 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:22:57 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size_type)
{
	void	*result;
	size_t	nbite;

	if (nmemb == 0 || size_type == 0)
		nbite = 1;
	else
		nbite = nmemb * size_type;
	result = malloc(nbite);
	if (result)
		ft_bzero(result, nbite);
	return (result);
}
