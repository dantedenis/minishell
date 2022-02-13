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

t_env	*g_env;

static void	echo_ctrl_off(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}
/*
static void	echo_ctrl_on(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}
*/
int main(int argc, char **argv, char **env)
{
	struct sigaction	sig_act;
	char				*str_input;
	//t_parser_out		*pars_out;		//список от парсера(примерно)

	parse_env(env);
	(void) argc;
	(void) argv;
	sig_act.sa_sigaction = sig_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sig_act, NULL);
	sigaction(SIGQUIT, &sig_act, NULL);		//найти инфу какие сигналы ловить
	sigaction(SIGKILL, &sig_act, NULL);
	echo_ctrl_off();
	put_wellcome();
	//echo_ctrl_on();
	while (1)
	{
		if (!(str_input = readline("MINISHELL >> ")))
			return (1);
		add_history(str_input);
		if (ft_strncmp("env", str_input, 3) == 0)
		{
			bin_env();
		}
		/*
		if (!(pars_out = parser(str_input)));
			return (1);
		execute(pars_out);
		*/
	}
	return (0);
}