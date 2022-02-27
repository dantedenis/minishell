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

static void	echo_ctrl_off(void)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	new.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &new);
}

int	main(int argc, char **argv, char **env)
{
	char	*str_input;
	t_data	*data;

	if (argc != 1 && argv)
		return (write(2, "Too much args!\n", 15) == 15);
	data = init_data(env);
	if (sigaction(SIGINT, &data->sig_act, NULL) == -1)
		bin_exit(data, -1);
	while (1)
	{
		data->fork_status = 0;
		data->valid_cmds = 0;
		signal(SIGQUIT, SIG_IGN);
		str_input = readline(get_value_env(data->env, "PROMT"));
		echo_ctrl_off();
		if (!str_input)
			bin_exit(data, -1);
		else if (!is_empty_line(str_input))
			add_history(str_input);
		if (preparser(str_input))
			ft_putendl_fd("Error: unclosed quotes", 2);
		else if (!is_empty_line(str_input))
			split_pipe(str_input, data);
		free(str_input);
		sigaction(SIGINT, &data->sig_act, NULL);
	}
	return (EXIT_SUCCESS);
}
