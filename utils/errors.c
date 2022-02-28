/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:33:31 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 15:33:54 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str, int perror_flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (perror_flag)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	return (1);
}

int	syntax_error(char *str)
{
	int	type;

	type = 0;
	if (is_redirect(*str))
	{
		type = check_redirect(str);
		if (type == LEFT_REDIR)
			str = "'<'";
		else if (type == DOUBLE_LEFT_REDIR)
			str = "'<<'";
		else if (type == RIGHT_REDIR)
			str = "'>'";
		else
			str = "'>>'";
	}
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
	return (2);
}
