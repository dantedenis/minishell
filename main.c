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

t_data	*init_data(char **env);

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
	int i = 0;
	while (i < 5)
	{
		if (!(str_input = readline("MINISHELL >> ")))
			return (EXIT_FAILER);
		add_history(str_input);
		if (preparser(str_input))
			ft_putendl_fd("Error: unclosed quotes", 2);
		else
			split_cmds(str_input, data);
		free(str_input);
		++i;
	}
	free_data(&data);
	return (0);
	// TODO: << stop cat | << stop cat
	// insert builtin in execute cmd
	// skip some builtins in pipes
}
