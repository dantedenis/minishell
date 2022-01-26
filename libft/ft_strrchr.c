/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:24:55 by lcoreen           #+#    #+#             */
/*   Updated: 2021/10/10 15:24:57 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = 0;
	while (*s != '\0')
	{
		if (*s == c)
			ret = (char *) s;
		++s;
	}
	if (c == '\0')
		return ((char *) s);
	else if (ret == 0)
		return ((void *) 0);
	else
		return (ret);
}
