#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/readline.h>
# include <fcntl.h>
# include <stdio.h>
# include "command.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# define RIGHT_REDIR 0
# define DOUBLE_RIGHT_REDIR 1
# define LEFT_REDIR 2
# define DOUBLE_LEFT_REDIR 3

int	preparser(char *str);
int	ft_error(char *str);
int	split_cmds(char *str, char **env);
void	print_list(t_list *lst);
t_cmd	*new_cmd(char *cmd);
int	parse_redir(char *cmd, char c, char **env);
int	execute_cmd(t_cmd *cmd, int *pipefd, char c, char **env);
int	close_files_and_pipe(t_cmd *cmd);
char	*get_cmd(char *str);
int		is_space(char c);
char	*join_list(t_list *lst);
int	is_desired_sign(char c);
int	is_redirect(char c);
int	check_redirect(char *str);
int	here_doc(t_cmd *cmd, char *stop);

/*
** HANDLE SPEC SYMBOLS
*/

char *slash(char *str, int *i, int in_quotes);
char *dollar(char *str, int *i);
char *quote(char *str, int *i);
char *double_quote(char *str, int *i);
int redir(t_cmd *cmd, char *str, int *i);

#endif