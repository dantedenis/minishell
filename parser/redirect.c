/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:38:05 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/01 13:31:26 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_argument(char *str, int is_heredoc, t_data *data)
{
	int		j;
	int		started_i;
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
		if (is_desired_sign(str[i], is_heredoc))
			ft_lstadd_back(&arg, ft_lstnew(handle_sign(data, str, &i)));
		if (str[i] && str[i] != '$' && started_i == i)
			++i;
		if (started_i + 1 != i)
			j = i;
	}
	ft_lstadd_back(&arg, ft_lstnew(ft_substr(str, j, i - j)));
	ret = join_list(arg);
	ft_lstclear(&arg, free);
	return (ret);
}

static int	open_file(t_data *data, char *file, int k)
{
	char	*parsed_file;

	parsed_file = parse_argument(file, 0, data);
	if (data->c[k]->type_redirect == RIGHT_REDIR)
	{
		if (data->c[k]->outf >= 0)
			close(data->c[k]->outf);
		data->c[k]->outf = open(parsed_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (data->c[k]->type_redirect == LEFT_REDIR)
	{
		if (data->c[k]->inf >= 0)
			close(data->c[k]->inf);
		data->c[k]->inf = open(parsed_file, O_RDONLY, 0644);
	}
	else if (data->c[k]->type_redirect == DOUBLE_RIGHT_REDIR)
	{
		if (data->c[k]->outf >= 0)
			close(data->c[k]->outf);
		data->c[k]->outf = open(parsed_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	if (data->c[k]->inf == -1 || data->c[k]->outf == -1)
		ft_error(file, 1);
	free(parsed_file);
	return (data->c[k]->inf == -1 || data->c[k]->outf == -1);
}

static int	here_doc(t_data *data, char *stop, int k)
{
	char	*line;
	char	*parsed_line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	if (!line)
		exit(ft_error("warning: heredoc delimited by end-of-file", 0));
	while (line)
	{
		if (!ft_strcmp(stop, line))
			break ;
		parsed_line = parse_argument(line, 1, data);
		ft_putendl_fd(parsed_line, data->c[k]->heredoc_pipe[1]);
		free(line);
		free(parsed_line);
		line = readline("> ");
		if (!line)
			exit(ft_error("warning: heredoc delimited by end-of-file", 0));
	}
	close_pipe(data->c[k]->heredoc_pipe);
	free(line);
	exit(EXIT_SUCCESS);
}

static int	fork_here_doc(t_data *data, char *stop, int k)
{
	pid_t	child;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (data->c[k]->heredoc_flag)
		close_pipe(data->c[k]->heredoc_pipe);
	pipe(data->c[k]->heredoc_pipe);
	child = fork();
	if (!child)
		here_doc(data, stop, k);
	wait_here_doc(data, child);
	data->c[k]->heredoc_flag = 1;
	return (data->status);
}

int	redir(t_data *data, char *str, int *i, int k)
{
	int		find_word;
	char	*file;

	data->c[k]->type_redirect = check_redirect(str + *i);
	*i += data->c[k]->type_redirect % 2 + 1;
	find_word = go_to_end_redir(str, i);
	file = ft_substr(str, find_word, *i - find_word);
	if (data->c[k]->type_redirect == DOUBLE_LEFT_REDIR)
	{
		if (fork_here_doc(data, file, k))
		{
			free(file);
			return (1);
		}
	}
	else if (open_file(data, file, k))
	{
		free(file);
		return (data->status = EXIT_FAILER);
	}
	free(file);
	return (0);
}
