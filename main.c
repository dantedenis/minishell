#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	
    (void) argv;
    (void) argc;
	str = readline("minish~$ ");
	if (preparser(str))
		return (ft_error("preparser error"));
	split_cmds(str, env);
	free(str);
	return (0);
}

// TODO: << stop cat | << stop cat

