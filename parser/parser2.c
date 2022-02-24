#include "minishell.h"

t_cmd *init_cmd(int have_pipe)
{
	t_cmd *ret;

	ret = (t_cmd *)malloc(sizeof(t_cmd));
	ret->inf = -2;
	ret->outf = -2;
	ret->have_pipe = have_pipe;
	ret->heredoc_flag = 0;
	ret->cmd = NULL;
	return (ret);
}

static int count_pipe(char *str)
{
	char quote;
	int i;
	int j;
	int ret;

	quote = 0;
	i = 0;
	ret = 0;
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
			++ret;
		if (str[i])
			++i;
	}
	return (ret);
}

static void	ft_newline_sigint(int wstatus, int *newline)
{
        if (WTERMSIG(wstatus) == SIGINT && *newline == 0)
        {
                *newline = *newline + 1;
                printf("\n");
        }
}


static void wait_cmds(t_data *data, char *str)
{
	int i;
	int size;
	int status;
	int	newline;

	size = count_pipe(str);
	i = 0;
	newline = 0;
	while (i < size)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFSTOPPED(status))
			data->status = WSTOPSIG(status) + 128;
		if (WIFSIGNALED(status))
		{
			ft_newline_sigint(status, &newline);
			data->status = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		i++;
	}
}

static int split_pipe(char *str, t_data *data)
{
	char quote;
	int i;
	int j;

	quote = 0;
	i = 0;
	signal(SIGINT, SIG_IGN);
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
		if (!quote && parser(ft_substr(str, j, i - j), str[i] == '|', data, )
		{
			dup2(data->dup_stdin, 0);
			free(str);
			return (1);
		}
		if (str[i])
			++i;
	}
	wait_cmds(data, str);
	dup2(data->dup_stdin, 0);
	free(str);
	return (0);
}

int split_cmds(char *str, t_data *data)
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
			split_pipe(ft_substr(str, j, i - j), data);
		if (str[i])
			++i;
	}
	return (0);
}
