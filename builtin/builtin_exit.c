/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:09 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:09 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_exit(t_data *data)
{
	tcsetattr(0, TCSANOW, &data->default_tty);
	close_files_and_pipe(data->cmd);
	ft_lstclear(&data->cmd->cmd, free);
	free(data->cmd);
	free_data(&data);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(1);
}