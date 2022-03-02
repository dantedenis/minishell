/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:15:54 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/02 10:40:29 by lcoreen          ###   ########.fr       */
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

static void	set_new_value_pwd(t_data *data)
{
	if (get_env(data->env, "OLDPWD"))
		export(&data->env, "OLDPWD", data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = getcwd(NULL, 0);
	if (get_env(data->env, "PWD"))
		export(&data->env, "PWD", data->pwd);
}

static int	change_dir(t_data *data, char *path, int flag, int fd)
{
	char	*cwd;

	if (!path)
		return (ft_error("cd: HOME/OLDPWD not set", 0));
	if (fd < 0)
		fd = 1;
	cwd = getcwd(NULL, 0);
	if (!cwd && !ft_strncmp(".", path, 2))
		return (ft_error(CD_ERROR, 0));
	free(cwd);
	if (!chdir(path))
	{
		if (flag)
			ft_putendl_fd(path, fd);
		set_new_value_pwd(data);
	}
	else
		return (cd_error(path));
	return (0);
}

int	bin_cd(t_data *data, t_list *cmd, int fd)
{
	if (!cmd)
		return (change_dir(data, get_value_env(data->env, "HOME"), 0, fd));
	else if (!ft_strncmp(cmd->content, "--", 3))
		return (change_dir(data, get_value_env(data->env, "HOME"), 0, fd));
	else if (!ft_strncmp(cmd->content, "-", 2))
		return (change_dir(data, data->oldpwd, 1, fd));
	else if (cmd->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		return (change_dir(data, cmd->content, 0, fd));
	return (0);
}
