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

void	put_env(char *data, t_env **env)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	if (*env)
	{
		new->str = ft_split(data, '=');
		new->key = new->str[0];
		new->value = new->str[1];
		new->next = *env;
		*env = new;
	}
	else
	{
		*env = new;
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

void		parse_env(char **str, t_env **env)
{
	while (*str)
		put_env(*str++, env);
	reverse_stack(env);
}

char	*get_value_env(t_env *env, char *key)
{
	t_env	*temp;
	int		len_key;

	temp = env;
	len_key = ft_strlen(key) + 1;
	while(temp)
	{
		if (!ft_strncmp(key, temp->key, len_key))
			return (ft_strdup(temp->value));
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

char	*get_item(t_env *env)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(env->key, "=");
	ret = ft_strjoin(tmp, env->value);
	free(tmp);
	return (ret);	
}

char	**transform_env_to_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	array = (char **) malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		array[i] = get_item(env);
		env = env->next;
		++i;
	}
	array[i] = NULL;
	return (array);
}
