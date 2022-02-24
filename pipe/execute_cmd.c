/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:13:58 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/24 19:40:19 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **transform_list_to_array(t_list *lst)
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

static int	check_builtin(char *str, t_data *data, int i)
{
	char	**tmp;
	int		tmp_status;

	// Чекаем про билтины в пайпах, если да, то запускаем в дочери
	// Если нет, то в родителе. fork_status - сообщает в каком процессе надо запускать
	// Флаг have_pipe сообщает где билтин находится и меняем соответствующее значение форкстатуса
	if (data->count_cmds > 1 && i < data->count_cmds - 1 && !data->fork_status)
		return (data->fork_status = 1);
	// Костыль: если в дочери, то меняем форк статус на какоето значение
	// Если после всех проверок форкстатус равен 2, значит билтин исполнился и надо чистить память и exit
	// Если форкстатус == 1, то эта команда не билтин и запускаемся бин через run_child
	if (data->fork_status == 1)
		data->fork_status = 2;
	if (!ft_strncmp(str, "export", 7))
	{
		// проверка на наличие аргумента, если нет, то пока запускаем env
		if (!data->c[i]->cmd->next)
			data->status = bin_env(data->env, data->c[i]->inf);
		// если есть агрумент в котором есть =, то исполняется export. Иначе ничего не происходит
		else if (data->c[i]->cmd->next->content && ft_strchr(data->c[i]->cmd->next->content, '='))
		{
			tmp = get_key_value(data->c[i]->cmd->next->content);
			data->status = bin_export(&data->env, tmp[0], tmp[1]);
			ft_freearr(&tmp);
		} // TODO: проверять аргумент export такие же правила как у unset, написать функцию проверки аргумента
	}
	else if (!ft_strncmp(str, "echo", 5))
		data->status = bin_echo(data->c[i]->cmd->next, data->c[i]->outf);
	else if (!ft_strncmp(str, "exit", 5))
		bin_exit(data, i);
	else if (!ft_strncmp(str, "env", 4))
		data->status = bin_env(data->env, data->c[i]->outf);
	else if (!ft_strncmp(str, "pwd", 4))
		data->status = bin_pwd(data->env, data->c[i]->outf);
	else if (!ft_strncmp(str, "cd", 3))
		data->status = bin_cd(&data->env, data->c[i]->cmd->next, data->c[i]->outf);
	else if (!ft_strncmp(str, "unset", 6))
		data->status = bin_unset(&data->env, data->c[i]->cmd->next);
	else
		data->fork_status = 1;
	// здесь используется костыльное значение форкстатуса
	if (data->fork_status == 2)
	{
		tmp_status = data->status;
		close_files_and_pipe(data->c[i]);
		free_data(&data);
		exit(tmp_status);
	}
	return (data->fork_status);
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

int	execute_cmd(t_data *data, int *pipefd, int i)
{
	pid_t	child;

	sigaction(SIGQUIT, &data->sig_qt, NULL);
	if (check_builtin(data->c[i]->cmd->content, data, i))
	{
		child = fork();
		if (!child)
		{
			if (data->count_cmds > 1 && i < data->count_cmds - 1)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
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
		else
			data->pid_arr[i] = child;
	}
	close_files_and_pipe(data->c[i]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
