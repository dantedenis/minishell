#include "minishell.h"

int	bin_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd, 1);
	free(pwd);
	return (0);
}