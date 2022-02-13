/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:33:22 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:33:22 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_env(char *data)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	if (g_env)
	{
		new->str = ft_split(data, '=');
		new->key = new->str[0];
		new->value = new->str[1];
		new->next = g_env;
		g_env = new;
	}
	else
	{
		g_env = new;
		new->next = NULL;
		new->str = ft_split(data, '=');
		new->key = new->str[0];
		new->value = new->str[1];
	}
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

void		parse_env(char **str)
{
	while (*str)
		put_env(*str++);
	reverse_stack(&g_env);
}

char	*get_value_env(char *key)
{
	t_env	*temp;
	int		len_key;

	temp = g_env;
	len_key = ft_strlen(key) + 1;
	while(temp)
	{
		if (!ft_strncmp(key, temp->key, len_key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*get_env(char *key)
{
	t_env	*temp;
	int		len_key;

	temp = g_env;
	len_key = ft_strlen(key) + 1;
	while(temp)
	{
		if (!ft_strncmp(key, temp->key, len_key))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}