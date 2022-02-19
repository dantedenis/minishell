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

static void	echo_ctrl_off(t_data *data)
{
	struct termios	new;

	tcgetattr(0, &new);
	data->default_tty = new;
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

int main(int argc, char **argv, char **env)
{
	struct sigaction	sig_act;
	char				*str_input;
	t_data				*data;

	if (argc != 1 && argv)
		return (write(2, "Too much args!\n", 15) == 15);
	data = init_data(env);
	echo_ctrl_off(data);
	sig_act.sa_sigaction = sig_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sig_act, NULL);
	signal(SIGQUIT, SIG_IGN);
	put_wellcome(data);
	while (1)
	{
		data->fork_status = 0;
		if (!(str_input = readline(get_value_env(data->env, "PROMT"))))
			return (EXIT_FAILER);
		add_history(str_input);
		if (preparser(str_input))
			ft_putendl_fd("Error: unclosed quotes", 2);
		else
			split_cmds(str_input, data);
		free(str_input);
	}
	//free_data(&data);
	return (EXIT_SUCCESS);
}
