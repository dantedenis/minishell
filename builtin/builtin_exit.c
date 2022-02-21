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
	int	tmp_status;

	tmp_status = 0;
	if (!data->fork_status)
		write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &data->default_tty);
	if (data->cmd->cmd->next)
		tmp_status = ft_atoi(data->cmd->cmd->next->content);
	if (data->cmd)
	{
		close_files_and_pipe(data->cmd);
		ft_lstclear(&data->cmd->cmd, free);
	}
	free(data->cmd);
	free_data(&data);
	rl_clear_history();
	exit(tmp_status);
}