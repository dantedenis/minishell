/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:26:56 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/02 00:25:20 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(1);
	data->env = NULL;
	data->c = NULL;
	data->pid_arr = NULL;
	tcgetattr(0, &data->default_tty);
	data->status = 0;
	data->sig_act.sa_sigaction = sig_handler;
	data->sig_act.sa_flags = SA_SIGINFO;
	data->sig_qt.sa_sigaction = sig_handler_quit;
	parse_env(env, &data->env);
	data->dir = ft_strdup(get_value_env(data->env, "PWD"));
	export(&data->env, "PROMT", PROMT);
	put_wellcome(data);
	return (data);
}

static void	free_env(t_env **env)
{
	t_env	*temp;
	t_env	*del_elem;

	temp = *env;
	while (temp)
	{
		del_elem = temp;
		temp = temp->next;
		free(del_elem->key);
		free(del_elem->value);
		free(del_elem);
	}
	*env = NULL;
}

void	free_data(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	free(tmp->dir);
	free_alloc_arrays(tmp);
	free_env(&tmp->env);
	free(*data);
	*data = NULL;
}

void	parse_env(char **str, t_env **env)
{
	while (*str)
		put_env(*str++, env);
	reverse_stack(env);
}
