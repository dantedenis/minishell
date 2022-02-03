#include "minishell.h"

void	bin_exit(t_list *list) //+ то что нужно очистить
{
	ft_lstclear(list, free);
	//
	//	add
	//
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(1);
}