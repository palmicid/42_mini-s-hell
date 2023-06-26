/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/26 20:08:27 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

// the child going to be parent for all program
void	process(void)
{
	t_cmd	*cmdlist;

	cmdlist = NULL;
	add_history(g_data->strcmd);
	// Why ??? becoz I'm too lazy to fix all inside this process
	cmdlist = str_split(g_data->strcmd, g_data);
	// test_print(cmdlist);
	// to execute
	to_execute(cmdlist);
	cmdlist = free_cmdlist(cmdlist);

}

int	main(int ac, char **av, char **env)
{
	// char	*strcmd;

	(void)ac;
	(void)av;
	g_data = (t_data *)malloc(sizeof(t_data));
	init_environ(env);
	signal_handling(1);
	while (1)
	{
		g_data->strcmd = readline("Minishell >> ");
		if (!g_data->strcmd)
			break ;
		else if (g_data->strcmd[0] == '\0')
			;
		else if (ft_strlen(g_data->strcmd) > 0)
			process();
		free(g_data->strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ());
}
