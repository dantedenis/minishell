#include "minishell.h"

int	ft_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	return (1);
}

int		is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' ||
		c == '\f' || c == '\n' || c == '\v');
}


void	print_list(t_list *lst)
{
	int	i;
	
	i = 0;
	while (lst)
	{
		printf("cmd %d: %s\n", i, lst->content);
		lst = lst->next;
		++i;
	}
}

int	open_file(t_cmd *cmd, char *file)
{
	if (cmd->type_redirect == RIGHT_REDIR)
	{
		if (cmd->outf != -1)
			close(cmd->outf);
		cmd->outf = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->outf < 0)
			return (ft_error(file));
	}
	else if (cmd->type_redirect == LEFT_REDIR)
	{
		if (cmd->inf != -1)
			close(cmd->inf);
		cmd->inf = open(file, O_RDONLY, 0644);
		if (cmd->inf < 0)
			return (ft_error(file));
	}
	else if (cmd->type_redirect == DOUBLE_RIGHT_REDIR)
	{
		if (cmd->outf != -1)
			close(cmd->outf);
		cmd->outf = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (cmd->outf < 0)
			return (ft_error(file));
	}
	return (0);
}

int	close_files_and_pipe(t_cmd *cmd)
{
	if (cmd->inf != -1)
		close(cmd->inf);
	if (cmd->outf != -1)
		close(cmd->outf);
	if (cmd->heredoc_flag)
	{
		close(cmd->heredoc_pipe[0]);
		close(cmd->heredoc_pipe[1]);
	}
	return (0);
}

void	free_cmd(void *cmd)
{
	t_cmd	*tmp;

	tmp = (t_cmd *) cmd;
	free(tmp->cmd);
	free(tmp);
}

char	*join_list(t_list *lst)
{
	char	*tmp;
	char	*ret;

	ret = ft_strdup(lst->content);
	while (lst->next)
	{
		tmp = ft_strjoin(ret, lst->next->content);
		free(ret);
		ret = tmp;
		lst = lst->next;
	}
	return (ret);
}

int	is_desired_sign(char c)
{
	return (c == '\'' || c == '"' || c == '$' || c == '\\');
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	check_redirect(char *str)
{
	char	redir;

	redir = str[0];
	if (str[1] == str[0])
	{
		if (str[0] == '>')
			return (DOUBLE_RIGHT_REDIR);
		else if (str[1] == '<')
			return (DOUBLE_LEFT_REDIR);
	}
	if (str[0] == '>')
		return (RIGHT_REDIR);
	return (LEFT_REDIR);
}
