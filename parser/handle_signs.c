/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:56:29 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/20 01:15:45 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *slash(char *str, int *i, int in_quotes)
{
	int j;
	int hide_slash;

	j = (*i)++;
	hide_slash = 1;
	if (in_quotes &&
		(str[*i + 1] != '"' && str[*i + 1] != '$' && str[*i + 1] != '\\'))
		hide_slash = 0;
	while (str[*i] && is_space(str[*i]))
		++(*i);
	return (ft_substr(str, j + hide_slash, *i - j - 1));
}

static char	*check_finish(char *item, char *str)
{
	char	*temp;

	if (!str || !*str)
		return (item);		//TODO!!! копию делать из подстроки, от ? до пробела или 0
	temp = item;
	item = ft_strjoin(item, str + 7);
	free(temp);
	return (item);
}

char	*dollar(char *str, int *i, t_data *data)
{
	int		j;
	char	*tmp;
	char	*item;

	j = (*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '?'))
		++(*i);
	if (*i - j - 1 == 0)
		return (ft_strdup("$"));
	tmp = ft_substr(str, j + 1, *i - j - 1);
	j = 0;
	if (!ft_strncmp("?", tmp, 1) && ++j)
		item = ft_itoa(data->status);
	else
		item = get_value_env(data->env, tmp);
	free(tmp);
	if (item == NULL)
		return (NULL);
	if (j)
	{
		item = check_finish(item, str);
		return (item);
	}
	return (ft_strdup(item));
}

char	*quote(char *str, int *i)
{
	int j;

	j = (*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	return (ft_substr(str, j + 1, *i - j - 1));
}

char	*double_quote(char *str, int *i, t_data *data)
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
			if (*i != j)
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
			tmp = dollar(str, i, data);
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
		if (str[*i] != '"' && str[*i] != '$')
			++(*i);
	}
	if (*i != j)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
	tmp = join_list(lst);
	ft_lstclear(&lst, free);
	return (tmp);
}
