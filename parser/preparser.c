/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:10:27 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/13 18:10:28 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int preparser(char *str)
{
	char quote;

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