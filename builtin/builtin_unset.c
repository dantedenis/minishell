/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:19 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:19 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_list(t_env *ptr)
{
	free(ptr->key);
	ptr->key = NULL;
	free(ptr->value);
	ptr->value = NULL;
	free(ptr);
	ptr = NULL;
	return (0);
}

int	bin_unset(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*pre;
	int		len_key;

	temp = *env;
	len_key = ft_strlen(key) + 1;
	if (!key)
		return (1);
	while (temp->next)
	{
		if (!ft_strncmp(key, temp->key, len_key))
		{
			*env = temp->next;
			return (free_list(temp));
		}
		else if (!ft_strncmp(key, temp->next->key, len_key))
		{
			pre = temp->next;
			temp->next = temp->next->next;
			return (free_list(pre));
		}
		temp = temp->next;
	}
	return (0);
}