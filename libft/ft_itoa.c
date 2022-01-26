/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:35:09 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:35:10 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		++len;
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*ret;
	int		flag;

	len = ft_intlen(n);
	ret = (char *) malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	flag = 1;
	if (n < 0)
	{
		ret[0] = '-';
		flag = -1;
	}
	else if (n == 0)
		ret[0] = '0';
	i = len;
	while (n)
	{
		ret[--i] = (n % 10) * flag + '0';
		n /= 10;
	}
	ret[len] = '\0';
	return (ret);
}
