/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:13:58 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 20:55:16 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**transform_list_to_array(t_list *lst)
{
	char	**array;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(lst);
	array = (char **) malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		array[i] = ft_strdup(lst->content);
		lst = lst->next;
		++i;
	}
	array[i] = NULL;
	return (array);
}

static void	run_child(t_data *data, int i)
{
	char	*cmd;
	char	**new_argv;
	char	**env;

	tcsetattr(0, TCSANOW, &data->default_tty);
	new_argv = transform_list_to_array(data->c[i]->cmd);
	cmd = get_cmd(data->env, new_argv[0]);
	if (!cmd)
		exit(ft_error(new_argv[0], 1));
	env = transform_env_to_array(data->env);
	free_data(&data);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd, new_argv, env);
	ft_error(new_argv[0], 1);
	free(cmd);
	ft_freearr(&new_argv);
	ft_freearr(&env);
	exit(1);
}

void	child(t_data *data, int *pipefd, int input, int i)
{
	if (data->count_cmds > 1 && i)
	{
		dup2(input, 0);
		close(input);
	}
	if (data->count_cmds > 1 && i + 1 < data->count_cmds)
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	check_builtin(data->c[i]->cmd->content, data, i);
	if (data->c[i]->inf != -1)
		dup2(data->c[i]->inf, 0);
	if (data->c[i]->heredoc_flag)
		dup2(data->c[i]->heredoc_pipe[0], 0);
	if (data->c[i]->outf != -1)
		dup2(data->c[i]->outf, 1);
	close_files_and_pipe(data->c[i]);
	run_child(data, i);
}

int	execute_cmd(t_data *data, int *pipefd, int input, int i)
{
	pid_t	pid;

	sigaction(SIGQUIT, &data->sig_qt, NULL);
	signal(SIGINT, SIG_IGN);
	if (check_builtin(data->c[i]->cmd->content, data, i))
	{
		pid = fork();
		if (!pid)
			child(data, pipefd, input, i);
		else
			data->pid_arr[data->valid_cmds] = pid;
		++data->valid_cmds;
	}
	close_files_and_pipe(data->c[i]);
	return (0);
}
