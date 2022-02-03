#include "minishell.h"

void	bin_env()
{
	t_env	*temp;

	temp = g_env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}