/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:38:53 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/03 14:26:22 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_fork_builtin(t_data *data, int i)
{
	int	tmp_status;

	tmp_status = data->status;
	close_files_and_pipe(data->c[i]);
	free_data(&data);
	exit(tmp_status);
}

int	check_builtin(char *str, t_data *data, int i)
{
	if (data->count_cmds > 1 && i < data->count_cmds - 1 && !data->fork_status)
		return (data->fork_status = 1);
	if (data->fork_status == 1)
		data->fork_status = 2;
	if (!ft_strncmp(str, "export", 7))
		bin_export(data, i);
	else if (!ft_strncmp(str, "echo", 5))
		data->status = bin_echo(data->c[i]->cmd->next, data->c[i]->outf);
	else if (!ft_strncmp(str, "exit", 5))
		bin_exit(data, i);
	else if (!ft_strncmp(str, "env", 4))
		data->status = bin_env(data->env, 0, data->c[i]->outf);
	else if (!ft_strncmp(str, "pwd", 4))
		data->status = bin_pwd(data->pwd, data->c[i]->outf);
	else if (!ft_strncmp(str, "cd", 3))
		data->status = bin_cd(data, data->c[i]->cmd->next, data->c[i]->outf);
	else if (!ft_strncmp(str, "unset", 6))
		data->status = bin_unset(data, i);
	else
		return (data->fork_status = 1);
	if (data->fork_status == 2)
		exit_fork_builtin(data, i);
	return (0);
}
