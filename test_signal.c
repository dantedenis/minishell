#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void	print_message(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	printf("%d %d", siginfo->si_uid, SIGCHLD);
    if (sig == SIGINT)
    {
        printf("SIGINT lol\n");
    }
    if (sig == SIGQUIT && siginfo->si_pid == SIGCHLD)
    {
        printf("exit Child\n");
        exit(0);
    }
}


int	main(void)
{
	struct sigaction	sig_act;
	pid_t   pid;

	sig_act.sa_sigaction = print_message;
	sig_act.sa_flags = SA_SIGINFO;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sig_act, NULL) == -1)
		    write(2, "SIGERROR!\n", 11);
	pid = fork();	
    if (!pid)
    {
        signal(SIGQUIT, SIG_DFL);
        if (sigaction(SIGQUIT, &sig_act, NULL) == -1)
		    write(2, "SIGERROR!\n", 11);
    	while (1)
    	{
    	    printf("Im CHild\n");
    		pause();
    	}
    }
    wait(&pid);
	while (1)
	{
	    printf("Im Parent\n");
		pause();

	}
	return (0);
}
