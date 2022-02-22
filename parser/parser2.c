#include "minishell.h"

t_cmd	*init_cmd(int have_pipe)
{
	t_cmd	*ret;

	ret = (t_cmd *) malloc(sizeof(t_cmd));
	ret->inf = -2;
	ret->outf = -2;
	ret->have_pipe = have_pipe;
	ret->heredoc_flag = 0;
	ret->cmd = NULL;
	return (ret);
}

static int	split_pipe(char *str, t_data *data)
{
	char	quote;
	int		i;
	int		j;

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
		if (!quote && parser(ft_substr(str, j, i - j), str[i] == '|', data))
		{
			dup2(data->dup_stdin, 0);
			free(str);
			return (1);
		}
		if (str[i])
			++i;
	}
	dup2(data->dup_stdin, 0);
	free(str);
	return (0);
}

int	split_cmds(char *str, t_data *data)
{
	char	quote;
	int		i;
	int		j;

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
			split_pipe(ft_substr(str, j, i - j), data);
		if (str[i])
			++i;
	}
	return (0);
}
