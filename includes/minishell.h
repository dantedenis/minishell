#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <termios.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

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
	int		have_pipe;
	int		heredoc_pipe[2];
	int		type_redirect;
	int		heredoc_flag;
}   t_cmd;

typedef struct s_data
{
	t_env			*env;
	t_cmd			*cmd;
	int				dup_stdin;
	int				status;
	int				fork_status;
	struct termios	default_tty;
}	t_data;

/*
** PARSER
*/

int	preparser(char *str);
int	split_cmds(char *str, t_data *env);

/*
** PIPE_&&_EXECUTION
*/

int	execute_cmd(t_data *data, int *pipefd);
char	*get_cmd(t_env *env, char *str);

/*
** UTILS_FUNCTIONS
*/

int	ft_error(char *str);
void	print_list(t_list *lst, char *lstmane);
int	close_files_and_pipe(t_cmd *cmd);
int		is_space(char c);
char	*join_list(t_list *lst);
int	is_desired_sign(char c, int is_heredoc);
int	is_redirect(char c);
int	check_redirect(char *str);
void	free_data(t_data **data);

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


void	parse_env(char **str, t_env **env);
char	*get_value_env(t_env *env, char *key);
void	put_env(char *str, t_env **env);
void	reverse_stack(t_env **head);
void	print_env(void);
t_env	*get_env(t_env *env, char *key);
char	**transform_env_to_array(t_env *env);

/*
**	BUILTIN_UTILS
*/

int		bin_echo(t_list *cmd);
int		bin_env(t_env *env);
void	bin_exit(t_data *data);
int		bin_pwd(void);
int		bin_unset(t_env **env, char *key);
int		bin_export(t_env **env, char *key, char *value);
int		bin_cd(t_env **env, t_list *cmd);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	put_wellcome(t_data *data);

#endif