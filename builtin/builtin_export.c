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

int	bin_export(t_env **env, char *key, char *value)
{
	t_env	*temp;

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