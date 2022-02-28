/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:35:18 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/28 20:53:35 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\f' || c == '\n' || c == '\v');
}

int	is_empty_line(char *s)
{
	while (is_space(*s))
		++s;
	return (!*s);
}

int	is_desired_sign(char c, int is_heredoc)
{
	if (is_heredoc)
		return (c == '$');
	return (c == '\'' || c == '"' || c == '$');
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
