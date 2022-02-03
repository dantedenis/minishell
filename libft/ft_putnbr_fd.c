/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:39:37 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/10 17:39:37 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	out;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		out = (~n + 1);
	}
	else
		out = n;
	if (out >= 10)
		ft_putnbr_fd(out / 10, fd);
	ft_putchar_fd(out % 10 + '0', fd);
}
