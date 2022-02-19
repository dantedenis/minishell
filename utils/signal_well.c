/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_well.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:26:58 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/19 20:26:58 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_wellcome(t_data *data)
{
	char	*buf;

	if ((buf = get_value_env(data->env, "LOGNAME")))
	{
		ft_putstr_fd("\033[5;34mHI ", 1);
		ft_putendl_fd(buf, 1);
		ft_putendl_fd("What will we do? ) \033[0m", 1);
	}
	else
		ft_putstr_fd("\033[5;34m HI anonim,!\nWhat will we do? ) \033[0m", 1);
}

void	sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 1);
		exit(130);
	}
}