/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:31:08 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/17 15:30:07 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int parse_argument(t_cmd *cmd, t_list **arg, char *str, int *i)
{
	int j;
	int started_i;

	j = *i;
	while (str[*i] && !is_space(str[*i]))
	{
		started_i = *i;
		if (is_desired_sign(str[*i], 0) && *i != j)
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
		{
			if (redir(cmd, str, i) == 1)
				return (-1);
		}
		if (str[*i] && (!is_redirect(str[*i]) && str[*i] != '$'))
			++(*i);
		if (started_i + 1 != *i)
			j = *i;
	}
	return (j);
}

static int get_arguments(t_cmd *cmd, char *str)
{
	t_list *arg;
	int i;
	int j;

	arg = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			++i;
		if (!str[i])
			break;
		j = parse_argument(cmd, &arg, str, &i);
		if (j == -1)
		{
			ft_lstclear(&arg, free);
			return (1);
		}
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

static t_cmd	*init_cmd(int have_pipe)
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

static int parser(char *str, int have_pipe, t_data *data)
{
	int		pipefd[2];

	if (have_pipe)
		pipe(pipefd);
	data->cmd = init_cmd(have_pipe);
	if (get_arguments(data->cmd, str) == 0)
	{
		free(str);
		execute_cmd(data, pipefd);
	}
	if (have_pipe)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	ft_lstclear(&data->cmd->cmd, free);
	free(data->cmd);
	return (0);
}

static int split_pipe(char *str, t_data *data)
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
		if (!quote)
			parser(ft_substr(str, j, i - j), str[i] == '|', data);
		if (str[i])
			++i;
	}
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
