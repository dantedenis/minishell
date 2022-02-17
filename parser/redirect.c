/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:38:05 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/17 20:19:45 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_argument(char *str, int is_heredoc)
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
			ft_lstadd_back(&arg, ft_lstnew(double_quote(str, &i)));
		else if (str[i] == '$')
			ft_lstadd_back(&arg, ft_lstnew(dollar(str, &i)));
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

static int	open_file(t_cmd *cmd, char *file)
{
	char	*parsed_filename;

	parsed_filename = parse_argument(file, 0);
	if (cmd->type_redirect == RIGHT_REDIR)
	{
		if (cmd->outf >= 0)
			close(cmd->outf);
		cmd->outf = open(parsed_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (cmd->type_redirect == LEFT_REDIR)
	{
		if (cmd->inf >= 0)
			close(cmd->inf);
		cmd->inf = open(parsed_filename, O_RDONLY, 0644);
	}
	else if (cmd->type_redirect == DOUBLE_RIGHT_REDIR)
	{
		if (cmd->outf >= 0)
			close(cmd->outf);
		cmd->outf = open(parsed_filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	if (cmd->inf == -1 || cmd->outf == -1)
		return (ft_error(file));
	free(parsed_filename);
	return (0);
}

static int	here_doc(t_cmd *cmd, char *stop)
{
	char	*line;
	char	*parsed_line;

	if (cmd->heredoc_flag)
	{
		close(cmd->heredoc_pipe[0]);
		close(cmd->heredoc_pipe[1]);
	}
	if (pipe(cmd->heredoc_pipe) < 0)
		return (ft_error("pipe"));
	line = readline("> ");
	if (!line)
		return (ft_error("malloc"));
	while (line)
	{
		if (!ft_strncmp(stop, line, ft_strlen(stop)))
			break ;
		parsed_line = parse_argument(line, 1);
		ft_putendl_fd(parsed_line, cmd->heredoc_pipe[1]);
		free(line);
		free(parsed_line);
		line = readline("> ");
		if (!line)
			return (ft_error("readline"));
	}
	cmd->heredoc_flag = 1;
	free(line);
	return (0);
}

int	redir(t_cmd *cmd, char *str, int *i)
{
	int		find_word;
	char	*file;

	find_word = 0;
	cmd->type_redirect = check_redirect(str + *i);
	*i += cmd->type_redirect % 2 + 1;
	while (str[*i] && ((!find_word && is_space(str[*i])) ||
			(!is_space(str[*i]) && !is_redirect(str[*i]))))
	{
		if (!find_word && !is_space(str[*i]))
			find_word = *i;
		++(*i);
	}
	file = ft_substr(str, find_word, *i - find_word);
	if (cmd->type_redirect == DOUBLE_LEFT_REDIR)
		here_doc(cmd, file);
	else if (open_file(cmd, file) == 1)
	{
		free(file);
		return (1);
	}
	free(file);
	return (0);
}
