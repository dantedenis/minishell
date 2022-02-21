/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:38:05 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/21 18:11:12 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_argument(char *str, int is_heredoc, t_data *data)
{
	int 	j;
	int 	started_i;
	t_list	*arg;
	int		i;
	char	*ret;

	i = 0;
	j = 0;
	arg = NULL;
	while (str[i])
	{
		started_i = i;
		if (is_desired_sign(str[i], is_heredoc) && i != j)
			ft_lstadd_back(&arg, ft_lstnew(ft_substr(str, j, i - j)));
		if (!is_heredoc && str[i] == '\'')
			ft_lstadd_back(&arg, ft_lstnew(quote(str, &i)));
		else if (!is_heredoc && str[i] == '"')
			ft_lstadd_back(&arg, ft_lstnew(double_quote(str, &i, data)));
		else if (str[i] == '$')
			ft_lstadd_back(&arg, ft_lstnew(dollar(str, &i, data)));
		if (str[i] && str[i] != '$')
			++i;
		if (started_i + 1 != i)
			j = i;
	}
	if (i != j)
		ft_lstadd_back(&arg, ft_lstnew(ft_substr(str, j, i - j)));
	ret = join_list(arg);
	ft_lstclear(&arg, free);
	return (ret);
}

static int	open_file(t_data *data, char *file)
{
	char	*parsed_file;

	parsed_file = parse_argument(file, 0, data);
	if (data->cmd->type_redirect == RIGHT_REDIR)
	{
		if (data->cmd->outf >= 0)
			close(data->cmd->outf);
		data->cmd->outf = open(parsed_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (data->cmd->type_redirect == LEFT_REDIR)
	{
		if (data->cmd->inf >= 0)
			close(data->cmd->inf);
		data->cmd->inf = open(parsed_file, O_RDONLY, 0644);
	}
	else if (data->cmd->type_redirect == DOUBLE_RIGHT_REDIR)
	{
		if (data->cmd->outf >= 0)
			close(data->cmd->outf);
		data->cmd->outf = open(parsed_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	if (data->cmd->inf == -1 || data->cmd->outf == -1)
		return (ft_error(file, 1));
	free(parsed_file);
	return (0);
}

static int	here_doc(t_data *data, char *stop)
{
	char	*line;
	char	*parsed_line;

	dup2(data->dup_stdin, 0);
	if (data->cmd->heredoc_flag)
	{
		close(data->cmd->heredoc_pipe[0]);
		close(data->cmd->heredoc_pipe[1]);
	}
	if (pipe(data->cmd->heredoc_pipe) < 0)
		return (ft_error("pipe", 1));
	line = readline("> ");
	if (!line)
		return (ft_error("malloc", 1));
	while (line)
	{
		if (!ft_strcmp(stop, line))
			break ;
		parsed_line = parse_argument(line, 1, data);
		ft_putendl_fd(parsed_line, data->cmd->heredoc_pipe[1]);
		free(line);
		free(parsed_line);
		line = readline("> ");
		if (!line)
			return (ft_error("readline", 1));
	}
	data->cmd->heredoc_flag = 1;
	free(line);
	return (0);
}

int	redir(t_data *data, char *str, int *i)
{
	int		find_word;
	char	*file;

	find_word = 0;
	data->cmd->type_redirect = check_redirect(str + *i);
	*i += data->cmd->type_redirect % 2 + 1;
	while (str[*i] && ((!find_word && is_space(str[*i])) ||
			(!is_space(str[*i]) && !is_redirect(str[*i]))))
	{
		if (!find_word && !is_space(str[*i]))
			find_word = *i;
		++(*i);
	}
	if (find_word == 0 && !str[*i])
		return (data->status = syntax_error("'newline'"));
	else if (find_word == 0 && is_redirect(str[*i]))
		return (data->status = syntax_error(str + *i));
	file = ft_substr(str, find_word, *i - find_word);
	if (data->cmd->type_redirect == DOUBLE_LEFT_REDIR)
		here_doc(data, file);
	else if (open_file(data, file) == 1)
	{
		free(file);
		return (EXIT_FAILER);
	}
	free(file);
	return (0);
}
