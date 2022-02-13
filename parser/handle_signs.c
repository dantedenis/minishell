#include "minishell.h"

char	*slash(char *str, int *i, int in_quotes)
{
	int		j;
	int		hide_slash;

	j = (*i)++;
	hide_slash = 1;
	if (in_quotes && 
		(str[*i + 1] != '"' && str[*i + 1] != '$' && str[*i + 1] != '\\'))
		hide_slash = 0;
	while (str[*i] && is_space(str[*i]))
		++(*i);
	return (ft_substr(str, j + hide_slash, *i - j - 1));
}

char	*dollar(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = (*i)++;
	while (str[*i] && ft_isalnum(str[*i]))
		++(*i);
	if (*i - j - 1 == 0)
		return (ft_strdup("$"));
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = getenv(tmp);
	free(tmp);
	if (tmp2 == NULL)
		return (NULL);
	tmp = ft_strdup(tmp2);
	return (tmp);
}

char	*quote(char *str, int *i)
{
	int	j;

	j = (*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	return (ft_substr(str, j + 1, *i - j - 1));
}

char	*double_quote(char *str, int *i)
{
	int		j;
	t_list	*lst;
	char	*tmp;

	j = ++(*i);
	lst = NULL;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
			tmp = dollar(str, i);
			if (tmp)
				ft_lstadd_back(&lst, ft_lstnew(tmp));
			j = *i;
		}
		else if (str[*i] == '\\')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
			tmp = slash(str, i, 1);
			ft_lstadd_back(&lst, ft_lstnew(tmp));
			j = *i;
		}
		++(*i);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
	tmp = join_list(lst);
	ft_lstclear(&lst, free);
	return (tmp);
}

int	redir(t_cmd *cmd, char *str, int *i)
{
	int		find_word;
	char	*file;

	find_word = 0;
	cmd->type_redirect = check_redirect(str + *i);
	*i += cmd->type_redirect % 2 + 1;
	while (str[*i] && ((!find_word && is_space(str[*i])) ||
			(!is_space(str[*i]) && !is_redirect(str[*i]))))
	{
		if (!find_word && !is_space(str[*i]))
			find_word = *i;
		++(*i);
	}
	file = ft_substr(str, find_word, *i - find_word);
	if (cmd->type_redirect == DOUBLE_LEFT_REDIR)
		here_doc(cmd, file);
	else if (open_file(cmd, file) == 1)
	{
		free(file);
		return (1);
	}
	free(file);
	return (0);
}
