#include "minishell.h"
#include "command.h"

// int	find_redir(char *str, int *i, char c)
// {
// 	size_t	i;
// 	int		r;
// 	int		find_word;
// 	char	*file;
// 	char	*redir;
// 	char	*tmp;
// 	char	*tmp2;

// 	redir = ft_strrchr((const char *) str, c);
// 	if (!redir)
// 		return (-1);
// 	i = redir - str;
// 	r = i++;
// 	find_word = 0;
// 	while (str[i] && ((!find_word && is_space(str[i])) ||
// 			!is_space(str[i])))
// 	{
// 		if (!find_word && !is_space(str[i]))
// 			find_word = i;
// 		++i;
// 	}
// 	file = ft_substr(str, find_word, i - find_word);
// 	tmp = ft_substr(str, 0, r);
// 	tmp2 = ft_strdup(str + i);
// 	free(str);
// 	find_word = open_file(file, c);
// 	if (find_word == -1)
// 		return (-2 + ft_error("Cant open file"));
// 	free(file);
// 	free(tmp);
// 	free(tmp2);
// 	return (str);
// }

int	parse_redir(char *cmd, char c, char **env)
{
	t_cmd	info;
	
	(void) env;
	info.is_full_cmd = 0;
	printf("before finding right redirect: %s\n", cmd);
	info.outf = find_redir(&cmd, '>');
	printf("after finding right redirect: %s\n", cmd);
	info.inf = find_redir(&cmd, '<');
	printf("after finding left redirect: %s\n", cmd);
	info.cmd = cmd;
	if (cmd[0] == '.' || cmd[0] == '/')
		info.is_full_cmd = 1;
	execute_cmd(&info, c, env);
	free(cmd);
	return (0);
}

int	execute_cmd(t_cmd *cmd, char c, char **env)
{
	int		pipefd[2];
	pid_t	child;

	if (c == '|')
		pipe(pipefd);
	child = fork();
	if (child == 0)
	{
		if (c == '|')
			close(pipefd[0]);
		if (cmd->inf != -1)
			dup2(cmd->inf, 0);
		if (cmd->outf != -1)
			dup2(cmd->outf, 1);
		else
			dup2(pipefd[1], 1);
		if (c == '|')
			close(pipefd[1]);
		close_files(cmd);
		run_child(cmd, env);
	}
	else if (child > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		wait(NULL);
		close(pipefd[0]);
		close_files(cmd);
	}
	return (0);
}
// TODO: Check leaks