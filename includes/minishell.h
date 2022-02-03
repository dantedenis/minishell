#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "command.h"
# include <sys/types.h>
# include <sys/wait.h>
int	preparser(char *str);
int	ft_error(char *str);
int	split_cmds(char *str, char **env);
void	print_list(t_list *lst);
t_cmd	*new_cmd(char *cmd);
int	parse_redir(char *cmd, char c, char **env);
int	open_file(t_cmd *cmd, char *file, char redir);
int	execute_cmd(t_cmd *cmd, char c, char **env);
int	close_files(t_cmd *cmd);
void	run_child(t_cmd *info, char **env);
char	*get_cmd(char *str);
int		is_space(char c);

#endif