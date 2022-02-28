/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:30:43 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 16:17:18 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (tmp)
	{
		if (tmp->cmd)
			ft_lstclear(&tmp->cmd, free);
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	*cmd = NULL;
}

void	free_array_cmd(t_cmd ***cmd, int size)
{
	int		i;
	t_cmd	**tmp;

	i = 0;
	tmp = *cmd;
	while (i < size)
	{
		if (tmp[i])
			free_cmd(tmp + i);
		++i;
	}
	free(tmp);
	*cmd = NULL;
}

void	free_alloc_arrays(t_data *data)
{
	if (data->pid_arr)
		free(data->pid_arr);
	data->pid_arr = NULL;
	if (data->c)
		free_array_cmd(&data->c, data->count_cmds);
}
