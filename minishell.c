/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/29 00:41:45 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*temp_pid;

// the child going to be parent for all program
static void	process(char *strcmd, t_data *data)
{
	int		stat;
	t_cmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	data->pid = fork();
	temp_pid = data->pid;
	if (data->pid == 0)
	{
		cmdlist = str_split(strcmd);
		// to execute
		test_print(cmdlist);
		// to_exec();
		// while (1)
		// {
		// 	printf("TEST =============  \n");
		// 	usleep(100000);
		// }
		cmdlist = free_cmdlist(cmdlist);
		exit(errno);
	}
	else if (data->pid < 0)
		strerror(errno);
	else
	{
		waitpid(data->pid, &stat, WNOHANG);
	}
}

static char	*sub_main(char *strcmd, t_data *data)
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
		process(strcmd, data);
	return (strcmd);
}

int	main(void)
{
	char	*strcmd;
	t_data	*data;

	strcmd = NULL;

	data = (t_data *)malloc(sizeof(data));
	if (!data)
		exit(EXIT_FAILURE);
	init_environ(data);
	signal_handling();
	while (1)
	{
		strcmd = sub_main(strcmd, data);
		if (!strcmd)
			break ;
		if (strcmd)
			free(strcmd);
	}
	if (!strcmd)
	{
		end_environ(data);
		ft_putendl_fd("exit", 1);
	}
	return (0);
}
