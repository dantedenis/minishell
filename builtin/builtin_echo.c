/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:02 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:02 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_echo(t_list *cmd, int fd)
{
	int		flag_n;

	if (fd < 0)
		fd = 1;
	if (!cmd)
		write(1, "\n", fd);
	else
	{
		flag_n = 1;
		while (cmd && !ft_strncmp(cmd->content, "-n", 3))
		{
			flag_n = 0;
			cmd = cmd->next;
		}
		while (cmd)
		{
			ft_putstr_fd(cmd->content, fd);
			if (cmd->next)
				ft_putchar_fd(' ', fd);
			cmd = cmd->next;
		}
		if (flag_n)
			ft_putstr_fd("\n", fd);
	}
	return (0);
}
