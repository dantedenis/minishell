/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:15 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:15 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_value_env(env, "PWD");
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	return (0);
}
