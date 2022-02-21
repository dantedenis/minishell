/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:24:12 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/21 20:02:39 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
