/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:15:54 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/22 16:15:13 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *path, int point)
{
	ft_putstr_fd(" cd: ", 2);
	if (point)
		ft_putstr_fd(".", 2);
	else
		ft_putstr_fd(path, 2);
	if (access(path, F_OK) == -1)
		ft_putendl_fd(": no such file or directory", 2);
	else if (access(path, R_OK) == -1)
		ft_putendl_fd(": permission denied", 2);
	else
		ft_putendl_fd(": not a directory", 2);
	return (1);
}

static int	change_dir(t_env **env, char *path, int flag, int fd)
{
	char	*cwd;
	int		point_path;

	if (fd < 0)
		fd = 1;
	point_path = 0;
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(path, ".", 2) && ++point_path)
		path = get_value_env(*env, "PWD");
	if (!chdir(path))
	{
		if (flag)
			ft_putendl_fd(path, fd);
		bin_export(env, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		bin_export(env, "PWD", cwd);
		free(cwd);
	}
	else
		return (cd_error(path, point_path));
	return (0);
}

int	bin_cd(t_env **env, t_list *cmd, int fd)
{
	if (!cmd)
		change_dir(env, get_value_env(*env, "HOME"), 0, fd);
	else if (!ft_strncmp(cmd->content, "--", 3))
		change_dir(env, get_value_env(*env, "HOME"), 0, fd);
	else if (!ft_strncmp(cmd->content, "-", 2))
		change_dir(env, get_value_env(*env, "OLDPWD"), 1, fd);
	else if (cmd->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		change_dir(env, cmd->content, 0, fd);
	return (0);
}
