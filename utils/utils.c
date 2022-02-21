#include "minishell.h"

void	free_cmd(t_cmd **cmd, int *pipefd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (tmp->have_pipe)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (tmp->cmd)
		ft_lstclear(&tmp->cmd, free);
	free(tmp);
	*cmd = NULL;
}

void	print_arr(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

int	ft_error(char *str, int perror_flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (perror_flag)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	return (1);
}

int	syntax_error(char *str)
{
	int	type;

	type = 0;
	if (is_redirect(*str))
	{
		type = check_redirect(str);
		if (type == LEFT_REDIR)
			str = "'<'";
		else if (type == DOUBLE_LEFT_REDIR)
			str = "'<<'";
		else if (type == RIGHT_REDIR)
			str = "'>'";
		else 
			str = "'>>'";
	}
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
	return (2);
}

int	is_empty_line(char *s)
{
	while (is_space(*s))
		++s;
	return (!*s);
}

int		is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' ||
		c == '\f' || c == '\n' || c == '\v');
}


void	print_list(t_list *lst, char *lstname)
{
	int	i;
	
	i = 0;
	while (lst)
	{
		printf("%s %d: %s\n", lstname, i, (char *)lst->content);
		lst = lst->next;
		++i;
	}
}

int	close_files_and_pipe(t_cmd *cmd)
{
	if (cmd->inf >= 0)
		close(cmd->inf);
	if (cmd->outf >= 0)
		close(cmd->outf);
	if (cmd->heredoc_flag)
	{
		close(cmd->heredoc_pipe[0]);
		close(cmd->heredoc_pipe[1]);
	}
	return (0);
}

char	*join_list(t_list *lst)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		if (!ret && lst->content)
			ret = ft_strdup(lst->content);
		if (ret && lst->next && lst->next->content)
		{
			tmp = ft_strjoin(ret, lst->next->content);
			free(ret);
			ret = tmp;
		}
		lst = lst->next;
	}
	if (!ret && lst->content)
		ret = ft_strdup(lst->content);
	return (ret);
}

int	is_desired_sign(char c, int is_heredoc)
{
	if (is_heredoc)
		return (c == '$');
	return (c == '\'' || c == '"' || c == '$');
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
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
