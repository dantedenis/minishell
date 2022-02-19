/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:13:58 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/19 16:14:24 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **transform_list_to_array(t_list *lst)
{
	char    **array;
	int     size;
	int     i;

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

static char	**get_key_value(char *str)
{
	int		i;
	char	**ret;
	char	*tmp;
	
	tmp = ft_strchr(str, '=');
	ret = (char **) malloc(sizeof(char *) * 3);
	i = tmp - str;
	ret[0] = ft_substr(str, 0, i);
	ret[1] = ft_strdup(tmp + 1);
	ret[2] = NULL;
	return (ret);	
}

static int	check_builtin(char *str, t_data *data)
{
	char	**tmp;
	int		tmp_status;
	
	if (data->cmd->have_pipe && !data->fork_status)
		return (data->fork_status = 1);
	if (data->fork_status == 1)
		data->fork_status = 2;
	if (!ft_strncmp(str, "export", 7))
	{
		if (!data->cmd->cmd->next)
			data->status = bin_env(data->env);
		else if (data->cmd->cmd->next->content && ft_strchr(data->cmd->cmd->next->content, '='))
		{
			tmp = get_key_value(data->cmd->cmd->next->content);
			data->status = bin_export(&data->env, tmp[0], tmp[1]);
			ft_freearr(&tmp);
		}
	}
	else if (!ft_strncmp(str, "echo", 5))
		data->status = bin_echo(data->cmd->cmd->next);
	else if (!ft_strncmp(str, "exit", 5))
		bin_exit(data);
	else if (!ft_strncmp(str, "env", 4))
		data->status = bin_env(data->env);
	else if (!ft_strncmp(str, "pwd", 4))
		data->status = bin_pwd();
	else if (!ft_strncmp(str, "cd", 3))
		data->status = bin_cd(&data->env, data->cmd->cmd->next);
	else if (!ft_strncmp(str, "unset", 6))
		data->status = bin_unset(&data->env, data->cmd->cmd->next);
	else
		data->fork_status = 1;
	if (data->fork_status == 2)
	{
		tmp_status = data->status;
		ft_lstclear(&data->cmd->cmd, free);
		free(data->cmd);
		free_data(&data);
		exit(tmp_status);
	}
	return (data->fork_status);
}

static void	run_child(t_data *data)
{
	char	*cmd;
	char	**new_argv;
	char	**env;

	new_argv = transform_list_to_array(data->cmd->cmd);
	cmd = get_cmd(data->env, new_argv[0]);
	if (!cmd)
		exit(ft_error(new_argv[0], 1));
	env = transform_env_to_array(data->env);
	ft_lstclear(&data->cmd->cmd, free);
	free(data->cmd);
	free_data(&data);
	execve(cmd, new_argv, env);
	ft_error(new_argv[0], 1);
	free(cmd);
	ft_freearr(&new_argv);
	ft_freearr(&env);
	exit(1);
}

int	execute_cmd(t_data *data, int *pipefd)
{
	int		status;

	if (check_builtin(data->cmd->cmd->content, data) && !fork())
	{
		if (data->cmd->have_pipe)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (data->cmd->inf != -1)
			dup2(data->cmd->inf, 0);
		if (data->cmd->heredoc_flag)
			dup2(data->cmd->heredoc_pipe[0], 0);
		if (data->cmd->outf != -1)
			dup2(data->cmd->outf, 1);
		close_files_and_pipe(data->cmd);
		if (check_builtin(data->cmd->cmd->content, data))
			run_child(data);
	}
	close_files_and_pipe(data->cmd);
	wait(&status);
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	return (0);
}
