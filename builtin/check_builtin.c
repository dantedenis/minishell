/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:38:53 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 21:05:00 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_builtin(char *str, t_data *data, int i)
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
			data->status = bin_env(data->env, 1, data->c[i]->inf);
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
		data->status = bin_env(data->env, 0, data->c[i]->outf);
	else if (!ft_strncmp(str, "pwd", 4))
		data->status = bin_pwd(data->env, data->c[i]->outf);
	else if (!ft_strncmp(str, "cd", 3))
		data->status = bin_cd(&data->env, data->c[i]->cmd->next, data->c[i]->outf);
	else if (!ft_strncmp(str, "unset", 6))
		data->status = bin_unset(&data->env, data->c[i]->cmd->next);
	else
		return (data->fork_status = 1);
	// здесь используется костыльное значение форкстатуса
	if (data->fork_status == 2)
	{
		tmp_status = data->status;
		close_files_and_pipe(data->c[i]);
		free_data(&data);
		exit(tmp_status);
	}
	return (0);
}