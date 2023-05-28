/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/28 17:38:18 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// the child going to be parent for all program
void	process(char *strcmd)
{
	int		stat;
	t_cmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		cmdlist = str_split(strcmd);
		// to execute
		test_print(cmdlist);
		// to_exec();
		exit(errno);
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
		return (NULL);
	else if (strcmd[0] == '\0')
		;
	else if (ft_strncmp(strcmd, "exit", 4) == 0)
	{
		free(strcmd);
		return (NULL);
	}
	else if (ft_strlen(strcmd) > 0)
		process(strcmd);
	return (strcmd);
}

int	main(void)
{
	char	*strcmd;

	strcmd = NULL;
	g_data = (t_data *)malloc(sizeof(t_data));
	if (!g_data)
		exit(EXIT_FAILURE);
	init_environ();
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
	{
		end_environ();
		ft_putendl_fd("exit", 1);
	}
	return (0);
}