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

static int	parse_argument(t_cmd *cmd, t_list **arg, char *str, int *i)
{
	int	j;
	int	started_i;

	j = *i;
	while (str[*i] && !is_space(str[*i]))	
	{
		started_i = *i;
		if (is_desired_sign(str[*i]) && *i != j)
			ft_lstadd_back(arg, ft_lstnew(ft_substr(str, j, *i - j)));
		if (str[*i] == '\'')
			ft_lstadd_back(arg, ft_lstnew(quote(str, i)));
		else if (str[*i] == '"')
			ft_lstadd_back(arg, ft_lstnew(double_quote(str, i)));
		else if (str[*i] == '$')
			ft_lstadd_back(arg, ft_lstnew(dollar(str, i)));
		else if (str[*i] == '\\')
			ft_lstadd_back(arg, ft_lstnew(slash(str, i, 0)));
		else if (str[*i] == '<' || str[*i] == '>')
			redir(cmd, str, i);
		if (str[*i])
			++(*i);
		if (started_i + 1 != *i)
			j = *i;
	}
	return (j);
}

static int	get_arguments(t_cmd *cmd, char *str)
{
	t_list	*arg;
	int		i;
	int		j;
	
	arg = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			++i;
		if (!str[i])
			break;
		j = parse_argument(cmd, &arg, str, &i);
		if (i != j)
			ft_lstadd_back(&arg, ft_lstnew(ft_substr(str, j, i - j)));
		if (arg)
		{
			ft_lstadd_back(&cmd->cmd, ft_lstnew(join_list(arg)));
			ft_lstclear(&arg, free);
		}
	}
	return (0);
}

static int	parser(char *str, char c, char **env)
{
	int 	i;
	t_cmd	cmd;

	i = 0;
	cmd.outf = -1;
	cmd.inf = -1;
	cmd.cmd = NULL;
	cmd.is_full_cmd = -1;
	cmd.heredoc_flag = 0;
	get_arguments(&cmd, str);
	execute_cmd(&cmd, c, env);
	free(str);
	ft_lstclear(&cmd.cmd, free);
	// close_files_and_pipe(&cmd);
	// if (cmd.type_redirect == DOUBLE_LEFT_REDIR)
		// dup2(g_dup_stdin, 0);
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
	// dup2(g_dup_stdin, 0);
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
