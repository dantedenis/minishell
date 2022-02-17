#include "minishell.h"

static void	change_dir(t_env **env, char *path, int flag)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (flag)
			ft_putstr_fd(get_value_env(*env, "OLDPWD"), 1);
		bin_export(env, "OLDPWD", cwd);
	}
	else
	{
		ft_putstr_fd(" cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK) == -1)
			ft_putstr_fd(": no such file or directory\n", 2);
		else if (access(path, R_OK) == -1)
			ft_putstr_fd(": permission denied\n", 2);
		else
			ft_putstr_fd(": not a directory\n", 2);
	}
	free(cwd);
}

int	bin_cd(t_env **env, t_list *cmd)
{
	if (!cmd->content)
		change_dir(env, get_value_env(*env, "HOME"), 0);
	else if (cmd->next->content)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (!ft_strncmp(cmd->content, "--", 3))
		change_dir(env, get_value_env(*env, "HOME"), 0);
	else if (!ft_strncmp(cmd->content, "-", 2))
		change_dir(env, get_value_env(*env, "OLDPWD"), 1);
	else
		change_dir(env, cmd->content, 0);
	return (0);
}
