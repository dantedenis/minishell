#include "libft.h"
#include <stdio.h>
#include "minishell.h"

char *slash(char *str, int *i, int in_quotes);
char *dollar(char *str, int *i);
char *quote(char *str, int *i);
char *double_quote(char *str, int *i);
int	redir(t_cmd *cmd, char *str, int *i);

int preparser(char *str)
{
	char quote;

	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		++str;
	}
	if (quote)
		return (1);
	return (0);
}

static int	parser(char *str, char c, char **env)
{
	int 	i;
	t_cmd	cmd;
	
	i = 0;
	cmd.outf = -1;
	cmd.inf = -1;
	// cmd.have_pipe = (c == '|');
	while (str[i])
	{
		if (str[i] == '\'')
			ft_lstadd_back(&cmd.cmd, ft_lstnew(ft_lstnew(quote(str, &i))));
		else if (str[i] == '"')
			ft_lstadd_back(&cmd.cmd, ft_lstnew(ft_lstnew(double_quote(str, &i))));
		else if (str[i] == '$')
			ft_lstadd_back(&cmd.cmd, ft_lstnew(ft_lstnew(dollar(str, &i))));
		else if (str[i] == '\\')
			ft_lstadd_back(&cmd.cmd, ft_lstnew(ft_lstnew(slash(str, &i, 0))));
		else if (str[i] == '<' || str[i] == '>')
			redir(&cmd, str, &i);
		++i;
	}
	execute_cmd(&cmd, c, env);
	free(str);
	ft_lstclear(&cmd.cmd, free);
	return (0);
}


static int	split_pipe(char *str, char **env)
{
	char quote;
	int i;
	int j;

	quote = 0;
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && (str[i] != '|' || quote))
		{
			if (!quote && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			++i;
		}
		if (!quote)
			parser(ft_substr(str, j, i - j), str[i], env);
		if (str[i])
			++i;
	}
	free(str);
	return (0);
}

int	split_cmds(char *str, char **env)
{
	char quote;
	int i;
	int j;

	quote = 0;
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && (str[i] != ';' || quote))
		{
			if (!quote && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			++i;
		}
		if (!quote)
			split_pipe(ft_substr(str, j, i - j), env);
		if (str[i])
			++i;
	}
	return (0);
}
