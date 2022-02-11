#include "minishell.h"
#include "command.h"

static char **transform_list_to_array(t_list *lst)
{
	char    **array;
	int     size;
	int     i;

	i = 0;
	size = ft_lstsize(lst);
	array = (char **) malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		array[i] = lst->content;
		lst = lst->next;
		++i;
	}
	array[i] = NULL;
	return (array);
}

static void	run_child(t_cmd *info, char **env)
{
	char	*cmd;
	char	**new_argv;

	new_argv = transform_list_to_array(info->cmd);
	cmd = get_cmd(new_argv[0]);
	execve(cmd, new_argv, env);
	perror("execve");
	free(cmd);
	ft_freearr(new_argv);
	exit(1);
}

int	here_doc(t_cmd *cmd, char *stop)
{
	char	*line;

	if (cmd->heredoc_flag)
	{
		close(cmd->heredoc_pipe[0]);
		close(cmd->heredoc_pipe[1]);
	}
	if (pipe(cmd->heredoc_pipe) < 0)
		return (ft_error("pipe in heredoc"));
	line = readline("> ");
	if (!line)
		return (ft_error("malloc"));
	while (line)
	{
		if (!ft_strcmp(stop, line))
			break ;
		ft_putendl_fd(line, cmd->heredoc_pipe[1]);
		free(line);
		line = readline("> ");
		if (!line)
			return (ft_error("malloc"));
	}
	cmd->heredoc_flag = 1;
	free(line);
	return (0);
}

int	execute_cmd(t_cmd *cmd, char c, char **env)
{
	int		pipefd[2];
	pid_t	child;
	int		status;

	if (c == '|')
		pipe(pipefd);
	child = fork();
	if (child == 0)
	{
		if (cmd->inf != -1)
			dup2(cmd->inf, 0);
		if (cmd->heredoc_flag)
			dup2(cmd->heredoc_pipe[0], 0);
		if (cmd->outf != -1)
			dup2(cmd->outf, 1);
		if (c == '|')
			dup2(pipefd[1], 1);		
		if (c == '|')
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		close_files_and_pipe(cmd);
		run_child(cmd, env);
	}
	else if (child > 0)
	{
		close_files_and_pipe(cmd);
		if (c == '|')
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		waitpid(child, &status, 0);
	}
	return (0);
}

