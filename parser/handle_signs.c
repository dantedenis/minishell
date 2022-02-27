/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:56:29 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/27 22:40:05 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_sign(t_data *data, char *str, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (str[*i] == '\'')
		tmp = quote(str, i);
	else if (str[*i] == '"')
		tmp = double_quote(str, i, data);
	else if (str[*i] == '$')
		tmp = dollar(str, i, data);
	return (tmp);
}

char	*dollar(char *str, int *i, t_data *data)
{
	int		j;
	char	*tmp;
	char	*item;

	j = (*i)++;
	if (str[*i] == '?' && (*i)++)
		return (ft_itoa(data->status));
	if (ft_isdigit(str[*i]) && (*i)++)
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		++(*i);
	if (*i - j - 1 == 0)
		return (ft_strdup("$"));
	tmp = ft_substr(str, j + 1, *i - j - 1);
	item = get_value_env(data->env, tmp);
	free(tmp);
	if (item == NULL)
		return (NULL);
	return (ft_strdup(item));
}

char	*quote(char *str, int *i)
{
	int		j;
	char	*tmp;

	j = (*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	tmp = ft_substr(str, j + 1, *i - j - 1);
	++(*i);
	return (tmp);
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
		if (str[*i] != '"' && str[*i] != '$')
			++(*i);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, j, *i - j)));
	tmp = join_list(lst);
	ft_lstclear(&lst, free);
	++(*i);
	return (tmp);
}
