/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:56:51 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/18 09:40:24 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_char(char *str, char ch)
{
	char	*path;
	int		i;

	i = 0;
	path = (char *) malloc(ft_strlen(str) + 2);
	if (!path)
		return (NULL);
	while (str[i])
	{
		path[i] = str[i];
		++i;
	}
	path[i++] = ch;
	path[i] = '\0';
	return (path);
}

static char	*check_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*temp_path;

	temp_path = add_char(path, '/');
	if (!temp_path)
		return (NULL);
	temp = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!temp)
		return (NULL);
	if (access(temp, X_OK) == 0)
		return (temp);
	free(temp);
	return (NULL);
}

static char	*find_cmd(char *str, char *cmd)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_split(str, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = check_cmd(paths[i], cmd);
		if (temp)
			break ;
		++i;
	}
	ft_freearr(&paths);
	return (temp);
}

char	*get_cmd(t_env *env, char *str)
{
	t_env	*path;
	char	*cmd;

	if (str[0] == '.' || str[0] == '/')
	{
		if (access(str, X_OK) == 0)
			return (ft_strdup(str));
		return (NULL);
	path = get_env(env, "PATH");
	if (!path)
	{
		if (access(str, X_OK) == 0)
			return (ft_strdup(str));
		return (NULL);
	}
	cmd = find_cmd(path->value, str);
	return (cmd);
}
