#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "command.h"

int	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
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

int	open_file(t_cmd *cmd, char *file, char redir)
{
	if (redir == '>')
	{
		if (cmd->outf != -1)
			close(cmd->outf);
		cmd->outf = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (redir == '<')
	{
		if (cmd->inf != -1)
			close(cmd->inf);
		cmd->inf = open(file, O_RDONLY);
	}
	return (0);
}

int	close_files(t_cmd *cmd)
{
	if (cmd->inf != -1)
		close(cmd->inf);
	if (cmd->outf != -1)
		close(cmd->outf);
	return (0);
}

t_cmd	*init_cmd(char *cmd)
{
	t_cmd	*elem;

	if (cmd == NULL)
		return (NULL);
	elem = (t_cmd *) malloc(sizeof(t_cmd));
	elem->cmd = cmd;
	elem->inf = -1;
	elem->outf = -1;
	elem->is_full_cmd = 0;
	return (elem);
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
	int		size;
	char	*tmp;
	char	*ret;

	size = ft_lstsize(lst);
	ret = ft_strdup(lst->content);
	if (size == 1)
		return (lst->content);
	while (lst->next)
	{
		tmp = ft_strjoin(ret, lst->next->content);
		free(ret);
		ret = tmp;
		lst = lst->next;
	}
	return (ret);
}