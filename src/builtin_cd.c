#include "minishell.h"

static void	change_dir(char *path, int flag)
{
	char	*cwd;

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

int	bin_cd(char **argv)
{
	char	*path_home;

	path_home = get_value_env("HOME");
	if (!argv[0])
	{
		change_dir(path_home, 0);
		return (0);
	}
}