/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:50:49 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/01 13:03:42 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	close_files_and_pipe(t_cmd *cmd)
{
	if (cmd->inf >= 0)
		close(cmd->inf);
	if (cmd->outf >= 0)
		close(cmd->outf);
	if (cmd->heredoc_flag)
		close_pipe(cmd->heredoc_pipe);
	return (0);
}

char	*join_list(t_list *lst)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		if (!ret && lst->content)
			ret = ft_strdup(lst->content);
		if (ret && lst->next && lst->next->content)
		{
			tmp = ft_strjoin(ret, lst->next->content);
			free(ret);
			ret = tmp;
		}
		lst = lst->next;
	}
	if (!ret && lst->content)
		ret = ft_strdup(lst->content);
	return (ret);
}

int	check_redirect(char *str)
{
	char	redir;

	redir = str[0];
	if (str[1] == str[0])
	{
		if (str[0] == '>')
			return (DOUBLE_RIGHT_REDIR);
		else if (str[1] == '<')
			return (DOUBLE_LEFT_REDIR);
	}
	if (str[0] == '>')
		return (RIGHT_REDIR);
	return (LEFT_REDIR);
}

int	go_to_end_redir(char *str, int *i)
{
	int	find_word;

	find_word = 0;
	while (str[*i] && ((!find_word && is_space(str[*i]))
			|| (!is_space(str[*i]) && !is_redirect(str[*i]))))
	{
		if (!find_word && !is_space(str[*i]))
			find_word = *i;
		++(*i);
	}
	return (find_word);
}
