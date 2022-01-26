/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:10:24 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 16:53:06 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_diglen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		++i;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'\
		|| *str == '\f' || *str == ' ' || *str == '\r')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	if (ft_isdigit(*str) && ((ft_diglen(str) > 19) || (ft_diglen(str) == 19 \
					&& ft_strncmp(str, "9223372036854775807", 19) > 0)))
		return ((-sign - 1) / 2);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * sign);
}
