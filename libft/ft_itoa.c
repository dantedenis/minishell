/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:26:25 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 00:26:25 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	len_rank(int num)
{
	int	rank;

	rank = 0;
	while (num)
	{
		num /= 10;
		++rank;
	}
	return (rank);
}

char	*ft_itoa(int n)
{
	char	buf[12];
	short	rank;

	rank = 0;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(buf, 12);
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
		++rank;
	}
	rank += len_rank(n);
	while (n)
	{
		buf[--rank] = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(buf));
}
