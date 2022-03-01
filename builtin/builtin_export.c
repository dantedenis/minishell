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

static char	**get_key_value(char *str)
{
	int		i;
	char	**ret;
	char	*tmp;

	ret = (char **) malloc(sizeof(char *) * 3);
	if (!ret)
		return (NULL);
	tmp = ft_strchr(str, '=');
	if (!tmp)
	{
		i = ft_strlen(str);
		ret[1] = NULL;
	}
	else
	{
		i = tmp - str;
		ret[1] = ft_strdup(tmp + 1);
	}
	ret[0] = ft_substr(str, 0, i);
	ret[2] = NULL;
	return (ret);
}

static int	checker(char *key)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		error = 1;
	while (key[++i])
	{
		if (!(ft_isalpha(key[i]) || ft_isdigit(key[i]) || key[i] == '_'))
		{
			error = 1;
			break ;
		}
	}
	if (error)
	{
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putendl_fd(key, 2);
		return (1);
	}
	return (0);
}

int	export(t_env **env, char *key, char *value)
{
	t_env	*temp;

	if (checker(key))
		return (1);
	temp = get_env(*env, key);
	if (!temp)
	{
		temp = (t_env *) malloc(sizeof(t_env));
		if (!temp)
			return (1);
		temp->key = ft_strdup(key);
		if (value)
			temp->value = ft_strdup(value);
		else
			temp->value = NULL;
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

int	bin_export(t_data *data, int i)
{
	char	**tmp;

	if (!data->c[i]->cmd->next)
		data->status = bin_env(data->env, 1, data->c[i]->inf);
	else if (data->c[i]->cmd->next->content)
	{
		tmp = get_key_value(data->c[i]->cmd->next->content);
		data->status = export(&data->env, tmp[0], tmp[1]);
		ft_freearr(&tmp);
	}
	return (data->status);
}
