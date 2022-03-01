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

static void	print_str(char *key, char *value, int export, int fd)
{
	if (export)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(key, fd);
	}
	else if (value)
		ft_putstr_fd(key, fd);
	if (value)
	{
		ft_putchar_fd('=', fd);
		if (export)
			ft_putchar_fd('"', fd);
		ft_putstr_fd(value, fd);
		if (export)
			ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

int	bin_env(t_env *env, int export, int fd)
{
	t_env	*temp;

	if (fd < 0)
		fd = 1;
	temp = env;
	while (temp)
	{
		print_str(temp->key, temp->value, export, fd);
		temp = temp->next;
	}
	return (0);
}
