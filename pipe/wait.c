/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:50:37 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/27 21:54:23 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_newline_sigint(int wstatus, int *newline)
{
	if (WTERMSIG(wstatus) == SIGINT && *newline == 0)
	{
			*newline = *newline + 1;
			printf("\n");
	}
}


void wait_cmds(t_data *data)
{
	int i;
	int status;
	int	newline;

	i = 0;
	newline = 0;
	while (i < data->valid_cmds)
	{
		waitpid(data->pid_arr[i], &status, WUNTRACED);
		if (WIFSTOPPED(status))
			data->status = WSTOPSIG(status) + 128;
		if (WIFSIGNALED(status))
		{
			ft_newline_sigint(status, &newline);
			data->status = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		i++;
	}
}