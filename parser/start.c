/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:20:36 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/02 16:00:58 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;
	int	ret;

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

static int	split_pipe(char *str, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*cur_cmd;

	i = 0;
	cur_cmd = 0;
	k = 0;
	while (str[i])
	{
		j = i;
		go_to_next_pipe(str, &i);
		cur_cmd = ft_substr(str, j, i - j);
		if (check_syntax(data, cur_cmd))
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
	return (0);
}

int	start(char *str, t_data *data)
{
	if (is_empty_line(str))
		return (1);
	if (str[ft_strlen(str) - 1] == '|')
		return (data->status = syntax_error("'|'"));
	alloc_array_cmds(data, str);
	if (split_pipe(str, data))
		return (1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	parser_and_execute(data);
	wait_cmds(data);
	free_alloc_arrays(data);
	return (0);
}
