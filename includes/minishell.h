/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:49:14 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/24 19:41:18 by lcoreen          ###   ########.fr       */
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

# define RIGHT_REDIR 0
# define DOUBLE_RIGHT_REDIR 1
# define LEFT_REDIR 2
# define DOUBLE_LEFT_REDIR 3
# define EXIT_FAILER 1
# define PROMT "👹\033[31;47mMINI⊗HELL\033[0m ⋙  "

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
	pid_t				*pid_arr;
	int					count_cmds;
	int					dup_stdin;
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
int		split_pipe(char *str, t_data *env);
void	parser(t_data *data);

/*
** PIPE_&&_EXECUTION
*/

int		execute_cmd(t_data *data, int *pipefd, int i);
char	*get_cmd(t_env *env, char *str);
void 	wait_cmds(t_data *data);
/*
** UTILS_FUNCTIONS
*/

int		ft_error(char *str, int perror_flag);
void	print_list(t_list *lst, char *lstmane);
int		close_files_and_pipe(t_cmd *cmd);
int		is_space(char c);
char	*join_list(t_list *lst);
int		is_desired_sign(char c, int is_heredoc);
int		is_redirect(char c);
int		check_redirect(char *str);
void	free_data(t_data **data);
void	print_arr(char **arr);
int		is_empty_line(char *s);
int		is_quote(char c);
int		syntax_error(char *str);
void	free_cmd(t_cmd **cmd);
void	free_array_cmd(t_cmd ***cmd, int size);

/*
** HANDLE_SPEC_SYMBOLS
*/

char	*slash(char *str, int *i, int in_quotes);
char	*dollar(char *str, int *i, t_data *data);
char	*quote(char *str, int *i);
char	*double_quote(char *str, int *i, t_data *data);
int		redir(t_data *data, char *str, int *i, int k);

/*
**	GLOBAL_VALUE_&&_UTILS
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
int		bin_env(t_env *env, int fd);
void	bin_exit(t_data *data, int i);
int		bin_pwd(t_env *env, int fd);
int		bin_unset(t_env **env, t_list *key);
int		bin_export(t_env **env, char *key, char *value);
int		bin_cd(t_env **env, t_list *cmd, int fd);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	sig_handler_quit(int sig, siginfo_t *siginfo, void *context);
void	put_wellcome(t_data *data);

#endif
