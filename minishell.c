/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 15:21:45 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process(t_data *g_data)
{
	t_cmdlist	*cmdlist;

	cmdlist = NULL;
	add_history(g_data->strcmd);
	cmdlist = str_split(g_data->strcmd, g_data);
	if (cmdlist)
		to_execute(cmdlist, g_data);
	cmdlist = free_cmdlist(&cmdlist);
}

int	main(int ac, char **av, char **env)
{
	t_data	*g_data;

	(void)ac;
	(void)av;
	g_data = (t_data *)malloc(sizeof(t_data));
	init_environ(env, g_data);
	while (1)
	{
		signal_handling(1);
		g_data->strcmd = readline("Minishell >> ");
		if (!g_data->strcmd)
			break ;
		else if (g_data->strcmd[0] == '\0')
			;
		else if (ft_strlen(g_data->strcmd) > 0)
			process(g_data);
		free(g_data->strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ(g_data));
}
