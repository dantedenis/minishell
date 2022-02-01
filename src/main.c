#include "minishell.h"

void	sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	//обработка сигналов.
}

int main(int argc, char **argv, char **env)
{
	struct sigaction	sig_act;
	char				*str_input;
	t_parser_out		*pars_out;		//список от парсера(примерно)

	sig_act.sa_sigaction = sig_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &sig_act, NULL);
	//sigaction(SIGQUIT, &sig_act, NULL);		//найти инфу какие сигналы ловить
	while (1)
	{
		if (!(str_input = readline("MINISHELL >> ")))
			return (EXIT_FAILER);
		add_history(str_input);
		if (!(pars_out = parser(str_input)));
			return (EXIT_FAILER);
		execute(pars_out);
	}
	return (0);
}