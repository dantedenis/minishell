#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/readline.h>
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
** HANDLE SPEC SYMBOLS
*/

char *slash(char *str, int *i, int in_quotes);
char *dollar(char *str, int *i);
char *quote(char *str, int *i);
char *double_quote(char *str, int *i);
int redir(t_cmd *cmd, char *str, int *i);

#endif