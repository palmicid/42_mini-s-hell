/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 21:23:49 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	cmdlist = str_split(strcmd, data);
	// to execute
	test_print(cmdlist);
	// data->exit_stat = to_execute(cmdlist);
	cmdlist = free_cmdlist(cmdlist);
	// exit(errno);
	// }
	// else if (data->pid < 0)
	// 	strerror(errno);
	// else
	// {
	// 	waitpid(data->pid, &stat, WNOHANG);
	// }
}

// char	*sub_main(char *strcmd, t_data *data)
// {
// 	return (strcmd);
// }

int	main(void)
{
	char	*strcmd;
	t_data	*data;

	strcmd = NULL;
	data = (t_data *)malloc(sizeof(t_data));
	init_environ(data);
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
			process(strcmd, data);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(data));
}
