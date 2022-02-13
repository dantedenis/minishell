/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:31:08 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/13 22:23:37 by lcoreen          ###   ########.fr       */
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

static int parser(char *str, char c, int dup_stdin, char **env)
{
	t_cmd	cmd;
	int		pipefd[2];

	if (c == '|')
		pipe(pipefd);
	cmd.outf = -2;
	cmd.inf = -2;
	cmd.cmd = NULL;
	cmd.is_full_cmd = -1;
	cmd.heredoc_flag = 0;
	if (get_arguments(&cmd, str) == 0)
		execute_cmd(&cmd, pipefd, c, env);
	if (c == '|')
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	free(str);
	ft_lstclear(&cmd.cmd, free);
	if (cmd.type_redirect == DOUBLE_LEFT_REDIR)
		dup2(dup_stdin, 0);
	return (0);
}

static int split_pipe(char *str, char **env)
{
	char	quote;
	int		i;
	int		j;
	int		dup_stdin;

	dup_stdin = dup(0);
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
			parser(ft_substr(str, j, i - j), str[i], dup_stdin, env);
		if (str[i])
			++i;
	}
	dup2(dup_stdin, 0);
	close(dup_stdin);
	free(str);
	return (0);
}

int split_cmds(char *str, char **env)
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
