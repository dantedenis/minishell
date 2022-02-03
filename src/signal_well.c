#include "minishell.h"

void	put_wellcome()
{
	char	*buf;

	if ((buf = get_value_env("USERNAME")))
	{
		ft_putstr_fd("\033[5m\033[34HI ", 1);
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("!\nWhat will we do? ) \033[0", 1);
		free(buf);
	}
	else
		ft_putstr_fd("\033[5m\033[34HI anonim,!\nWhat will we do? ) \033[0", 1);
}

void	sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	(void) context;
	if (signal == SIGINT)
	{
		
	}
}