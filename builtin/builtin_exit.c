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

void	bin_exit(t_data *data, int i)
{
	int	tmp_status;

	tmp_status = 0;
	tcsetattr(0, TCSANOW, &data->default_tty);
	if (!data->fork_status)
		write(1, "exit\n", 5);
	if (i >= 0 && data->c[i])
	{
		if (data->c[i]->cmd->next)
			tmp_status = ft_atoi(data->c[i]->cmd->next->content);
		close_files_and_pipe(data->c[i]);
	}
	free_data(&data);
	rl_clear_history();
	exit(tmp_status);
}
