/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:13:58 by lcoreen           #+#    #+#             */
/*   Updated: 2022/02/14 17:54:26 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **transform_list_to_array(t_list *lst)
{
	char    **array;
	int     size;
	int     i;

	i = 0;
	size = ft_lstsize(lst);
	array = (char **) malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		array[i] = lst->content;
		lst = lst->next;
		++i;
	}
	array[i] = NULL;
	return (array);
}

static void	run_child(t_cmd *info, char **env)
{
	char	*cmd;
	char	**new_argv;

	new_argv = transform_list_to_array(info->cmd);
	cmd = get_cmd(new_argv[0]);
	if (!cmd)
		exit(ft_error(new_argv[0]));
	execve(cmd, new_argv, env);
	ft_error(new_argv[0]);
	free(cmd);
	ft_freearr(new_argv);
	exit(1);
}

int	execute_cmd(t_cmd *cmd, int *pipefd, char c, char **env)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == 0)
	{
		if (c == '|')
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (cmd->inf != -1)
			dup2(cmd->inf, 0);
		if (cmd->heredoc_flag)
			dup2(cmd->heredoc_pipe[0], 0);
		if (cmd->outf != -1)
			dup2(cmd->outf, 1);
		close_files_and_pipe(cmd);
		run_child(cmd, env);
	}
	close_files_and_pipe(cmd);
	waitpid(child, &status, 0);
	return (0);
}
