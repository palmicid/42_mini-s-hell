#include "minishell.h"

pid_t	pid = 0;

void	sig_handle(int signo, siginfo_t *s, void *old)
{
	(void)old;
	(void)s;
	if (signo == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handling(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_sigaction = sig_handle;
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = SA_SIGINFO;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
	
	
}

void	ft_process(char *strcmd)
{
	// pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			printf("test kill = %s\n", strcmd);
			sleep(2);
		}
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		
		waitpid(pid, &stat, WNOHANG);
	}
}

int	main(void)
{
	char	*strcmd;
	// receive signal before enter while loop
	signal_handling();
	while (1)
	{
		strcmd = readline("Minishell >> ");
		if (strcmd[0] == '\0')
			;
		else if (ft_strncmp(strcmd, "exit", 4) == 0)
		{
			free(strcmd);
			break ;
		}
		else if (ft_strlen(strcmd) > 0)
		{	
			// cut string in to part and sent to exec
			ft_process(strcmd);
		}
		if (strcmd)
			free(strcmd);
	}
	return (0);
}
