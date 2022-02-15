#include "minishell.h"

void	put_wellcome(t_data *data)
{
	char	*buf;

	if ((buf = get_value_env(data->env, "LOGNAME")))
	{
		ft_putstr_fd("\033[5;34mHI ", 1);
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("!\nWhat will we do? ) \033[0m\n", 1);
		free(buf);
	}
	else
		ft_putstr_fd("\033[5m\033[34m HI anonim,!\nWhat will we do? ) \033[0m", 1);
}

void	sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		//rl_replace_line("", 0);
		//write(1, "\n", 1);
		//rl_on_new_line();
		//rl_redisplay();
		return ;
	}
	if (signal == SIGKILL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(1);
	}
}