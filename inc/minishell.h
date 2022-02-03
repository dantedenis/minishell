#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
//# include <readline/redline.h>
//# include <readline/history.h>

typedef struct s_env
{
	char			**str;
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

/*
**	GLOBAL_VALUE_&&_UTILS
*/

extern t_env	*g_env;

int		parse_env(char **str);
char	*get_value_env(char *key);
void	put_env(char *str);
void	reverse_stack(t_env **head);
void	print_env();
t_env	*get_env(char *key);

/*
**	BUILTIN_UTILS
*/

int		bin_echo(t_list **ptr);
void	bin_env();
void	bin_exit(t_list *list);
int		bin_pwd();
int		bin_unset(char *key);
int		bin_export(char *key, char *value);
int		bin_cd(char **str);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/


//void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	put_wellcome();

#endif