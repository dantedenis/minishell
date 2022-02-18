/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:26:56 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/18 09:47:50 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	data->env = NULL;
	data->dup_stdin = dup(0);
	data->status = 0;
	parse_env(env, &data->env);
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
		del_elem->key = NULL;
		del_elem->value = NULL;
		ft_freearr(&del_elem->str);
		free(del_elem);
	}
	*env = NULL;
}


void	free_data(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	close(tmp->dup_stdin);
	free_env(&tmp->env);
	free(*data);
	*data = NULL;
}
