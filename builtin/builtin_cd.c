/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:15:54 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/17 21:15:54 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dir(t_env **env, char *path, int flag)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (flag)
			ft_putendl_fd(path, 1);
		bin_export(env, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		bin_export(env, "PWD", cwd);
	}
	else
	{
		ft_putstr_fd(" cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK) == -1)
			ft_putendl_fd(": no such file or directory", 2);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd(": permission denied", 2);
		else
			ft_putendl_fd(": not a directory", 2);
	}
	free(cwd);
}

int	bin_cd(t_env **env, t_list *cmd)
{
	if (!ft_strncmp(cmd->content, "--", 3))
		change_dir(env, get_value_env(*env, "HOME"), 0);
	else if (!ft_strncmp(cmd->content, "-", 2))
		change_dir(env, get_value_env(*env, "OLDPWD"), 1);
	else if (cmd->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else
		change_dir(env, cmd->content, 0);
	return (0);
}
