/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:15:54 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/24 12:56:12 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
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

	if (fd < 0)
		fd = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd && !ft_strncmp(".", path, 2))
		return (ft_error("cd: the current working directory has been unlinked", 0));
	if (!cwd)
		cwd = ft_strdup(get_value_env(*env, "PWD"));
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
		return (cd_error(path));
	return (0);
}

int	bin_cd(t_env **env, t_list *cmd, int fd)
{
	if (!cmd)
		return (change_dir(env, get_value_env(*env, "HOME"), 0, fd));
	else if (!ft_strncmp(cmd->content, "--", 3))
		return (change_dir(env, get_value_env(*env, "HOME"), 0, fd));
	else if (!ft_strncmp(cmd->content, "-", 2))
		return (change_dir(env, get_value_env(*env, "OLDPWD"), 1, fd));
	else if (cmd->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		return (change_dir(env, cmd->content, 0, fd));
	return (0);
}
