/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:44:05 by bstrong           #+#    #+#             */
/*   Updated: 2022/02/04 23:44:05 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			**str;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*
**	GLOBAL_VALUE_&&_UTILS
*/

extern t_env	*g_env;

void	parse_env(char **str);
char	*get_value_env(char *key);
void	put_env(char *str);
void	reverse_stack(t_env **head);
void	print_env(void);
t_env	*get_env(char *key);

/*
**	BUILTIN_UTILS
*/

int		bin_echo(char *str);
void	bin_env(void);
void	bin_exit(t_list *list);
int		bin_pwd(void);
int		bin_unset(char *key);
int		bin_export(char *key, char *value);
int		bin_cd(char **str);

/*
**	SIGNAL_UTILS_&&_WELCOME
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context);
void	put_wellcome(void);

#endif