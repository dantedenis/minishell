/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:22:42 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 16:43:50 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(char *str)
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

int	check_syntax(t_data *data, char *str)
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
