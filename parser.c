#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	preparser(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		++str;
	}
	if (quote)
		return (1);
	return (0);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

char	*slash(char *str, int *i)
{
	char	*tmp1;
	char	*tmp2;

	if (str[*i + 1] != '"' && str[*i + 1] != '$' && str[*i + 1] != '\\')
		return (str);
	tmp1 = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	--(*i);
	return (str);
}

char	*dollar(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*half1;

	j = (*i)++;
	while (ft_isalnum(str[*i]))
		(*i)++;
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = ft_substr(str, 0, j);
	half1 = ft_strjoin(tmp2, getenv(tmp));
	free(tmp);
	if (half1 == NULL)
		half1 = tmp2;
	else
		free(tmp2);
	tmp = ft_strdup(str + *i);
	str = ft_strjoin(half1, tmp);
	*i = ft_strlen(half1);
	free(tmp);
	free(half1);
	return (str);
}

char	*quote(char *str, int *i)
{
	int	j;
	t_list	*tmp;
	char	*joined1;

	tmp = NULL;
	j = (*i)++;
	while (str[*i] != '\'')
		(*i)++;
	ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, 0, j)));
	ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, j + 1, *i - j - 1)));
	ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(str + *i + 1)));
	free(str);
	joined1 = ft_strjoin(tmp->content, tmp->next->content);
	str = ft_strjoin(joined1, tmp->next->next->content);
	free(joined1);
	ft_lstclear(&tmp, free);
	*i -= 2;
	return (str);
}

char	*double_quote(char *str, int *i)
{
	int	j;
	t_list	*tmp = NULL;
	char	*joined1;
	char	*joined2;

	j = (*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			str = dollar(str, i);
		else if (str[*i] == '\\')
			str = slash(str, i);
		++(*i);
	}
	ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, 0, j)));
	ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, j + 1, *i - j - 1)));
	ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(str + *i + 1)));
	joined1 = ft_strjoin(tmp->content, tmp->next->content);
	joined2 = ft_strjoin(joined1, tmp->next->next->content);
	free(joined1);
	free(str);
	ft_lstclear(&tmp, free);
	*i -= 2;
	return (joined2);
}

char	*parser(char *str, char **envp)
{
	int		i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str = quote(str, &i);
		else if (str[i] == '"')
			str = double_quote(str, &i);
		else if (str[i] == '$')
			str = dollar(str, &i);
		++i;
	}
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("\"abc $USERzxc\"");
	tmp = parser(str, envp);
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}