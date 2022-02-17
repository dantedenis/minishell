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

///////////////////////////////
/*
**		НУЖНО ИГРАТЬ ОТ ПАРАМЕТРА
*/
//////////////////////////


#include "minishell.h"

int	bin_echo(t_list *cmd)
{
	int		flag_n;

	if (!cmd->content)
		write(1, "\n", 1);
	else
	{
		flag_n = ft_strncmp(cmd->content, "-n", 3);
		if (flag_n)
			cmd = cmd->next;
		ft_putstr_fd(cmd->content, 1);
		if (!flag_n)
			write(1, "\n", 1);
	}
	return (0);
}