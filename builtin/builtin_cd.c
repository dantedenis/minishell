#include "minishell.h"

static void	change_dir(char *path, int flag)
{
	char	*cwd;

	(void) flag;
	cwd = getcwd(NULL, 0);
	if(!chdir(path))
	{
		bin_export("OLDPWD", cwd);
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

int	bin_cd(t_env *env, char **argv)
{
	if (!argv[0])
	{
		change_dir(get_value_env(env, "HOME"), 0);
		return (0);
	}
	if (argv[1])
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		if (!ft_strncmp(argv[0], "--", 3))
		{
			change_dir(get_value_env(env, "HOME"), 0);
			return (0);
		}
		else if (!ft_strncmp(argv[0], "-", 2))
		{
			change_dir(get_value_env(env, "OLDPWD"), 1);
			return (0);
		}
		change_dir(argv[0], 0);
	}
	return (0);
}