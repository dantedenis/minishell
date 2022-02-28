/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:06 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:06 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_env(t_env *env, int export, int fd)
{
	t_env	*temp;

	if (fd < 0)
		fd = 1;
	temp = env;
	while (temp)
	{
		if (export)
			ft_putsrt_fd("declare -x ", fd);
		if (key->value || export)
		{
			ft_putstr_fd(temp->key, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(temp->value, fd);
		}
		temp = temp->next;
	}
	return (0);
}
