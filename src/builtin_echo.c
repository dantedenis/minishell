///////////////////////////////
/*
**		НУЖНО ИГРАТЬ ОТ ПАРАМЕТРА
*/
//////////////////////////


#include "minishell.h"

int	bin_echo(char *str)
{
	int		flag_n;

	flag_n = ft_strncmp(str, "-n", 2);
	if (!flag_n)
		str = str + 2;
	ft_putstr_fd(str, 1);
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}