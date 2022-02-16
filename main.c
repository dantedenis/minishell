/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:26 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:26 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*init_data(char **env)
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


static void	free_data(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	close(tmp->dup_stdin);
	free_env(&tmp->env);
	free(*data);
	*data = NULL;
}

int main(int argc, char **argv, char **env)
{
	struct sigaction	sig_act;
	char				*str_input;
	t_data				*data;

	data = init_data(env);
	(void) argc;
	(void) argv;
	sig_act.sa_sigaction = sig_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &sig_act, NULL);
	//sigaction(SIGQUIT, &sig_act, NULL);		//найти инфу какие сигналы ловить
	put_wellcome(data);
	while (1)
	{
		if (!(str_input = readline("MINISHELL >> ")))
			return (EXIT_FAILER);
		add_history(str_input);
		if (preparser(str_input))
			ft_putendl_fd("Error: unclosed quotes", 2);
		else
			split_cmds(str_input, data);
		free(str_input);
	}
	free_data(&data);
	return (0);
	// TODO: << stop cat | << stop cat
}
