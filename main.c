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
/*
static void	echo_ctrl_off()
{
	struct termios	new;

	signal(SIGQUIT, SIG_IGN);
	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	new.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &new);
}
*/
int	main(int argc, char **argv, char **env)
{
	char				*str_input;
	t_data				*data;

	if (argc != 1 && argv)
		return (write(2, "Too much args!\n", 15) == 15);
	data = init_data(env);
	if (sigaction(SIGINT, &data->sig_act, NULL) == -1)			//TODO: ctrl+\ когда чтото написано должен выйти -_- (wat?)
		bin_exit(data);
	while (1)
	{
		data->fork_status = 0;
		str_input = readline(get_value_env(data->env, "PROMT"));		//TODO: readline когда печатаешь больше символов чем длина терминала перезаписывают первую строку, а потом делает перевод
		//echo_ctrl_off();
		if (!str_input)
			bin_exit(data);
		else if(!is_empty_line(str_input))
			add_history(str_input);
		if (preparser(str_input))
			ft_putendl_fd("Error: unclosed quotes", 2);
		else if (!is_empty_line(str_input))
			split_cmds(str_input, data);
		free(str_input);
	}
	return (EXIT_SUCCESS);
}
