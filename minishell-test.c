/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 00:17:09 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*temp_pid;

// the child going to be parent for all program
void	process(char *strcmd, t_data *data)
{
	// int		stat;
	t_cmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	// data->pid = fork();
	// temp_pid = &data->pid;
	// if (data->pid == 0)
	// {
	data->pid = fork();
	if (data->pid == 0)
	{
		cmdlist = str_split(strcmd);
	// to execute
		test_print(cmdlist);
		data->exit_stat = to_execute(cmdlist);
		cmdlist = free_cmdlist(cmdlist);
		exit(errno);
	}
	// }
	// else if (data->pid < 0)
	// 	strerror(errno);
	// else
	// {
	// 	waitpid(data->pid, &stat, WNOHANG);
	// }
}


int	main(void)
{
	char	*strcmd;
	int		runstat = 1;
	t_data	*data;

	strcmd = NULL;
	data = (t_data *)malloc(sizeof(t_data));
	init_environ(data);
	signal_handling();
	while (runstat)
	{
		// strcmd = sub_main(strcmd, &data);
		strcmd = readline("Minishell >> ");
		if (!strcmd)
			runstat = 0;
		else if (strcmd[0] == '\0')
			;
		else if (ft_strncmp(strcmd, "exit", 4) == 0)
			free(strcmd);
		else if (ft_strlen(strcmd) > 0)
			process(strcmd, data);
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
