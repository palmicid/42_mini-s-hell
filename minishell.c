/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/25 12:14:21 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

// the child going to be parent for all program
void	process(char *strcmd)
{
	int		stat;
	t_cmd	*cmdtable;
	// struct to store cmd and file

	cmdtable = NULL;
	add_history(strcmd);
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		while (1)
		{
			printf("PRINT TEST\n");
			sleep(1);
		}
		// string cut
		// cmdtable = str_split(strcmd, cmdtable);
		// to execute
		// to_exec();
		exit(EXIT_SUCCESS);
	}
	else if (g_data->pid < 0)
		strerror(errno);
	else
	{
		waitpid(g_data->pid, &stat, WNOHANG);
	}
}

char	*sub_main(char *strcmd)
{
	strcmd = readline("Minishell >> ");
	if (!strcmd)
		return(NULL);
	else if (strcmd[0] == '\0')
		;
	else if (ft_strncmp(strcmd, "exit", 4) == 0)
	{
		free(strcmd);
		return(NULL);
	}
	else if (ft_strlen(strcmd) > 0)
		process(strcmd);
	return (strcmd);
}

int	main(int ac, char **av, char **env)
{
	char	*strcmd;
	
	strcmd = NULL;
	g_data = (t_data *)malloc(sizeof(t_data));
	if (!g_data)
		exit(EXIT_FAILURE);
	(void)ac;
	(void)av;
	g_data->env = env;
	signal_handling();
	while (1)
	{
		strcmd = sub_main(strcmd);
		if (!strcmd)
			break ;
		if (strcmd)
			free(strcmd);
	}
	if (!strcmd)
		ft_putendl_fd("exit", 1);
	return (0);
}
