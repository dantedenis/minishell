#include "minishell.h"

t_env	*g_env;

int main(int argc, char **argv, char **env)
{
	parse_env(env);
	if(!g_env)
		printf("NULL\n");
	printf("%s\n\n", get_value_env("HOME"));
	bin_pwd();
	char *str = NULL;
	bin_cd(&str);
	/*bin_unset("PATH");
	bin_unset("ACLOCAL_PATH");
	bin_unset("MSYSTEM");
	bin_unset("MSYSDIR");
	bin_unset("OLDPWD");*/
	//bin_export("PATH", "aaaaaa");
	//bin_export("blaba", "ololo");
	//bin_env();
	printf("%s\n\n", get_value_env("OLDPWD"));
	return (0);
}
