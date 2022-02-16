#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RIGHT_REDIR 0
# define DOUBLE_RIGHT_REDIR 1
# define LEFT_REDIR 2
# define DOUBLE_LEFT_REDIR 3

# define EXIT_FAILER 1

typedef struct s_env
{
	char			**str;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	t_list	*cmd;
	int		inf;
	int		outf;
	int		is_full_cmd;
	int		have_pipe;
	int		dup_stdin;
	int		heredoc_pipe[2];
	int		type_redirect;
	int		heredoc_flag;
}   t_cmd;

int	preparser(char *str);
int	ft_error(char *str);
int	split_cmds(char *str, char **env);
void	print_list(t_list *lst, char *lstmane);
t_cmd	*new_cmd(char *cmd);
int	parse_redir(char *cmd, char c, char **env);
int	execute_cmd(t_cmd *cmd, int *pipefd, char c, char **env);
int	close_files_and_pipe(t_cmd *cmd);
char	*get_cmd(char *str);
int		is_space(char c);
char	*join_list(t_list *lst);
int	is_desired_sign(char c, int is_heredoc);
int	is_redirect(char c);
int	check_redirect(char *str);

/*
** HANDLE_SPEC_SYMBOLS
*/

char *slash(char *str, int *i, int in_quotes);
char *dollar(char *str, int *i);
char *quote(char *str, int *i);
char *double_quote(char *str, int *i);
int redir(t_cmd *cmd, char *str, int *i);

/*
**	GLOBAL_VALUE_&&_UTILS
*/

extern t_env	*g_env;

void	parse_env(char **str);
char	*get_value_env(char *key);
void	put_env(char *str);
void	reverse_stack(t_env **head);
void	print_env(void);
t_env	*get_env(char *key);

/*
**	BUILTIN_UTILS
*/

int		bin_echo(char *str);
void	bin_env(void);
void	bin_exit(t_list *list);
int		bin_pwd(void);
int		bin_unset(char *key);
int		bin_export(char *key, char *value);
int		bin_cd(char **str);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	put_wellcome(void);

#endif