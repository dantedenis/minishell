/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:31:08 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 16:15:06 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_argument(t_data *data, t_list **arg, int *i, int k)
{
	int		j;
	int		started_i;
	char	*tmp;

	j = *i;
	while (data->c[k]->str[*i] && !is_space(data->c[k]->str[*i]))
	{
		tmp = NULL;
		started_i = *i;
		if (is_desired_sign(data->c[k]->str[*i], 0) && *i != j)
			ft_lstadd_back(arg, ft_lstnew(ft_substr(data->c[k]->str, j, *i - j)));
		if (is_desired_sign(data->c[k]->str[*i], 0))
			tmp = handle_sign(data, data->c[k]->str, i);
		else if (is_redirect(data->c[k]->str[*i]) && \
			redir(data, data->c[k]->str, i, k))
				return (-1);
		if (tmp)
			ft_lstadd_back(arg, ft_lstnew(tmp));
		if (started_i != *i)
			j = *i;
		if (data->c[k]->str[*i] && started_i == *i)
			++(*i);
	}
	return (j);
}

static int	get_arguments(t_data *data, int k)
{
	t_list	*arg;
	int		i;
	int		j;

	arg = NULL;
	i = 0;
	while (data->c[k]->str[i])
	{
		while (data->c[k]->str[i] && is_space(data->c[k]->str[i]))
			++i;
		if (!data->c[k]->str[i])
			break ;
		j = parse_argument(data, &arg, &i, k);
		if (j == -1)
		{
			ft_lstclear(&arg, free);
			return (1);
		}
		if (i != j)
			ft_lstadd_back(&arg, ft_lstnew(ft_substr(data->c[k]->str, j, i - j)));
		if (arg)
			ft_lstadd_back(&data->c[k]->cmd, ft_lstnew(join_list(arg)));
		ft_lstclear(&arg, free);
	}
	return (0);
}

void	parser_and_execute(t_data *data)
{
	int	i;
	int	pipefd[2];
	int	input;

	i = 0;
	input = -1;
	while (i < data->count_cmds)
	{
		if (data->count_cmds > 1 && i + 1 < data->count_cmds)
			pipe(pipefd);
		data->fork_status = 0;
		if (!get_arguments(data, i) && data->c[i]->cmd)
			execute_cmd(data, pipefd, input, i);
		if (data->count_cmds > 1)
		{
			if (i)
				close(input);
			input = pipefd[0];
			if (i + 1 < data->count_cmds)
				close(pipefd[1]);
		}
		++i;
	}
}
