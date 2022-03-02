/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:49:14 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/02 10:24:27 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RIGHT_REDIR 2
# define DOUBLE_RIGHT_REDIR 1
# define LEFT_REDIR 4
# define DOUBLE_LEFT_REDIR 3
# define EXIT_FAILER 1
# define PROMT "👹\033[31;47mMINI⊗HELL\033[0m ⋙  "
# define CD_ERROR "cd: the current working directory has been unlinked"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	t_list	*cmd;
	char	*str;
	int		inf;
	int		outf;
	int		have_pipe;
	int		heredoc_pipe[2];
	int		type_redirect;
	int		heredoc_flag;
}	t_cmd;

typedef struct s_data
{
	t_env				*env;
	t_cmd				**c;
	char				*pwd;
	char				*oldpwd;
	pid_t				*pid_arr;
	int					valid_cmds;
	int					count_cmds;
	int					status;
	int					fork_status;
	struct termios		default_tty;
	struct sigaction	sig_act;
	struct sigaction	sig_qt;
}	t_data;

/*
** PARSER
*/

int		preparser(char *str);
int		start(char *str, t_data *env);
void	parser_and_execute(t_data *data);

/*
** PIPE_&&_EXECUTION
*/

int		execute_cmd(t_data *data, int *pipefd, int input, int i);
char	*get_cmd(t_env *env, char *str);
void	wait_cmds(t_data *data);
void	wait_here_doc(t_data *data, pid_t child);

/*
** UTILS_FUNCTIONS
*/

t_cmd	*init_cmd(char *str);

int		ft_error(char *str, int perror_flag);
int		syntax_error(char *str);
int		command_not_found(char *str);

void	print_list(t_list *lst, char *lstmane);
void	print_arr(char **arr);

int		is_desired_sign(char c, int is_heredoc);
int		is_redirect(char c);
int		is_empty_line(char *s);
int		is_quote(char c);
int		is_space(char c);

void	free_data(t_data **data);
void	free_array_cmd(t_cmd ***cmd, int size);
void	free_alloc_arrays(t_data *data);

int		close_files_and_pipe(t_cmd *cmd);
void	close_pipe(int *pipefd);

int		check_redirect(char *str);
char	*join_list(t_list *lst);
int		check_syntax(t_data *data, char *str);
int		go_to_end_redir(char *str, int *i);

/*
** HANDLE_SPEC_SYMBOLS
*/

char	*dollar(char *str, int *i, t_data *data);
char	*quote(char *str, int *i);
char	*double_quote(char *str, int *i, t_data *data);
int		redir(t_data *data, char *str, int *i, int k);
char	*handle_sign(t_data *data, char *str, int *i);

/*
**	ENV_&&_UTILS
*/

t_data	*init_data(char **env);
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

int		bin_echo(t_list *cmd, int fd);
int		bin_env(t_env *env, int export, int fd);
int		bin_exit(t_data *data, int i);
int		bin_pwd(char *dir, int fd);
int		bin_unset(t_env **env, t_list *key);
int		bin_cd(t_data *data, t_list *cmd, int fd);
int		bin_export(t_data *data, int i);
int		export(t_env **env, char *key, char *value);
int		check_builtin(char *str, t_data *data, int i);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	sig_handler_quit(int sig, siginfo_t *siginfo, void *context);
void	put_wellcome(t_data *data);

#endif
