#include "minishell.h"

static t_cmd	*init_cmd(char *str)
{
	t_cmd *ret;

	ret = (t_cmd *) malloc(sizeof(t_cmd));
	ret->inf = -2;
	ret->outf = -2;
	ret->str = str;
	ret->heredoc_flag = 0;
	ret->cmd = NULL;
	return (ret);
}

static void	go_to_next_pipe(char *str, int *i)
{
	char	quote;

	quote = 0;
	while (str[*i] && (str[*i] != '|' || quote))
	{
		if (!quote && (str[*i] == '\'' || str[*i] == '"'))
			quote = str[*i];
		else if (quote && str[*i] == quote)
			quote = 0;
		++(*i);
	}
}

static int	count_pipe(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		go_to_next_pipe(str, &i);
		++ret;
		if (str[i])
			++i;
	}
	return (ret);
}

static void	alloc_array_cmds(t_data *data, char *str)
{
	data->count_cmds = count_pipe(str);
	data->c = (t_cmd **) malloc(sizeof(t_cmd *) * data->count_cmds);
	data->pid_arr = (pid_t *) malloc(sizeof(pid_t) * data->count_cmds);
}

void	free_alloc_arrays(t_data *data)
{
	free(data->pid_arr);
	data->pid_arr = NULL;
	free_array_cmd(&data->c, data->count_cmds);
}

static int	check_cmd(t_data *data, char *str)
{
	int	i;
	int	found_redirect;
	
	found_redirect = 0;
	if (is_empty_line(str))
		return (data->status = syntax_error("'|'"));
	i = 0;
	while (str[i])
	{
		if (!found_redirect && is_redirect(str[i]))
		{
			found_redirect = check_redirect(str + i);
			if (found_redirect == DOUBLE_LEFT_REDIR || found_redirect == DOUBLE_RIGHT_REDIR)
				++i;
		}
		else if (found_redirect && is_redirect(str[i]))
			return (data->status = syntax_error(str + i));
		else if (!is_space(str[i]))
			return (0);
		++i;
	}
	if (found_redirect && !str[i])
		return (data->status = syntax_error("'newline'"));
	return (0);
}

int	split_pipe(char *str, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*cur_cmd;

	i = 0;
	cur_cmd = 0;
	k = 0;
	signal(SIGINT, SIG_IGN);
	if (is_empty_line(str))
		return (1);
	if (str[ft_strlen(str) - 1] == '|')
		return (data->status = syntax_error("'|'"));
	alloc_array_cmds(data, str);
	while (str[i])
	{
		j = i;
		go_to_next_pipe(str, &i);
		cur_cmd = ft_substr(str, j, i - j);
		if (check_cmd(data, cur_cmd))
		{
			free(cur_cmd);
			free_alloc_arrays(data);
			return (1);
		}
		data->c[k] = init_cmd(cur_cmd);
		++k;
		if (str[i])
			++i;
	}
	parser(data);
	wait_cmds(data);
	free_alloc_arrays(data);
	return (0);
}
