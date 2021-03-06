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

	buf = get_value_env(data->env, "LOGNAME");
	if (buf)
	{
		ft_putstr_fd("\033[5;34mHI ", 1);
		ft_putendl_fd(buf, 1);
		ft_putendl_fd("What will we do? ) \033[0m", 1);
	}
	else
		ft_putstr_fd("\033[5;34m HI anonim,!\nWhat will we do? ) \033[0m", 1);
}

void	sig_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_quit(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
}
