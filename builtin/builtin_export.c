/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:12 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:12 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(char *key, char *value)
{
	int	error;
	int	i;

	error = 0;
	i  = 0;
	if (!ft_isalpha(key[i]) || key[i] != '_')
		error = 1;
	if (!ft_strchr(value, '='))
		error = 1;
	while(key[++i])
	{
		if (!ft_isalpha(key[i]) || !ft_isdigit(key[i]))
		{
			error = 1;
			break ;
		}
	}
	if (error)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(key, 2);
		ft_putchar_fd('=', 2);
		ft_putstr_fd(value, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	return (0);
}

int	bin_export(t_env **env, char *key, char *value)
{
	t_env	*temp;

	if (checker(key, value))
		return (1);
	temp = get_env(*env, key);
	if (!temp)
	{
		temp = (t_env *) malloc(sizeof(t_env));
		if (!temp)
			return (1);
		temp->key = ft_strdup(key);
		temp->value = ft_strdup(value);
		temp->next = *env;
		*env = temp;
	}
	else
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
	return (0);
}
