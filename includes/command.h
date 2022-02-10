#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd
{
	t_list	*cmd;
	int		inf;
	int		outf;
	int		is_full_cmd;
	int		have_pipe;
	int		heredoc_pipe;
	int		heredoc_flag;
}   t_cmd;
t_cmd	*init_cmd(char *cmd);
void	free_cmd(void *cmd);
int	open_file(t_cmd *cmd, char *file, int type);

#endif
