/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:12 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:32:16 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		flag;

	flag = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		flag = -1;
	}
	if (n / 10 != 0)
	{
		ft_putnbr_fd((n / 10) * flag, fd);
		ft_putchar_fd((n % 10) * flag + '0', fd);
	}
	else
		ft_putchar_fd(n * flag + '0', fd);
}
