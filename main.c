#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	
    (void) argv;
    (void) argc;
	// g_dup_stdin = dup(0);
	str = readline("minish~$ ");
	if (preparser(str))
		return (ft_error("preparser error"));
	split_cmds(str, env);
	free(str);
	// close(g_dup_stdin);
	return (0);
}

// #include <unistd.h>
// #include <stdio.h>

// int main(int argc, char **argv, char **env)
// {
// 	char *args[] = {"/usr/bin/cat", "../ex", NULL};
// 	execve(args[0], args, env);
// 	printf("hey\n");
// 	return (0);
// }

// int main(int argc, char **argv, char **env)
// {
	
// 	printf("lyalyalya\n");
// 	return (0);
// }
