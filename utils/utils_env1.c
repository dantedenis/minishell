/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:23:55 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/19 20:23:55 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_env(char *data, t_env **env)
{
	t_env	*new;
	char	**item;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	if (*env)
	{
		item = ft_split(data, '=');
		new->key = ft_strdup(item[0]);
		new->value = ft_strdup(item[1]);
		new->next = *env;
		*env = new;
	}
	else
	{
		*env = new;
		new->next = NULL;
		item = ft_split(data, '=');
		new->key = ft_strdup(item[0]);
		new->value = ft_strdup(item[1]);
	}
	ft_freearr(&item);
}

void	reverse_stack(t_env **head)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*next;

	if (!*head || !(*head)->next)
		return ;
	curr = *head;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

char	*get_value_env(t_env *env, char *key)
{
	t_env	*temp;
	int		len_key;

	temp = env;
	len_key = ft_strlen(key) + 1;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, len_key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*get_env(t_env *env, char *key)
{
	t_env	*temp;
	int		len_key;

	temp = env;
	len_key = ft_strlen(key) + 1;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, len_key))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
