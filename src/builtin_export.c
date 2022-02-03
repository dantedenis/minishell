#include "minishell.h"

int	bin_export(char *key, char *value)
{
	t_env	*temp;

	temp = get_env(key);
	if (!temp)
	{
		temp = (t_env *) malloc(sizeof(t_env));
		if (!temp)
			return (1);
		temp->key = ft_strdup(key);
		temp->value = ft_strdup(value);
		temp->next = g_env;
		g_env = temp;
	}
	else
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
	return (0);
}