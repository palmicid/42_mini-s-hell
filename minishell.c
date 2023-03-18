/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/18 12:38:40 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

void	process(char *strcmd, char **env)
{
	int		stat;

	(void)env;
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		ft_putendl_fd(strcmd, 1);
		exit(EXIT_SUCCESS);
	}
	else if (g_data->pid < 0)
		strerror(errno);
	else
	{
		waitpid(g_data->pid, &stat, WNOHANG);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*strcmd;
	
	(void)ac;
	(void)av;
	g_data = (t_data *)malloc(sizeof(t_data));
	signal_handling();
	while (1)
	{
		strcmd = readline("Minishell >> ");
		if (!strcmd)
			break ;
		else if (strcmd[0] == '\0')
			;
		else if (ft_strncmp(strcmd, "exit", 4) == 0)
		{
			free(strcmd);
			break ;
		}
		else if (ft_strlen(strcmd) > 0)
			process(strcmd, env);
		if (strcmd)
			free(strcmd);
	}
	if (!strcmd)
		ft_putendl_fd("exit", 1);
	return (0);
}
