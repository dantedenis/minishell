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

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	bin_exit(t_data *data, int i)
{
	int	tmp_status;

	tmp_status = 0;
	tcsetattr(0, TCSANOW, &data->default_tty);
	if (!data->fork_status)
		write(1, "exit\n", 5);
	if (i >= 0 && data->c[i])
	{
		if (ft_lstsize(data->c[i]->cmd) > 2)
			return (data->status = ft_error("exit: too many arguments", 0));
		if (data->c[i]->cmd->next && is_number(data->c[i]->cmd->next->content))
			tmp_status = ft_atoi(data->c[i]->cmd->next->content);
		else if (data->c[i]->cmd->next)
		{
			ft_error("exit: numeric argument required", 0);
			tmp_status = 2;
		}
		close_files_and_pipe(data->c[i]);
	}
	free_data(&data);
	rl_clear_history();
	exit(tmp_status);
}
