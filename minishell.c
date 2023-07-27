/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 03:05:18 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

void	process(void)
{
	t_cmdlist	*cmdlist;

	cmdlist = NULL;
	add_history(g_data->strcmd);
	cmdlist = str_split(g_data->strcmd, g_data);
	if (cmdlist)
		to_execute(cmdlist);
	cmdlist = free_cmdlist(&cmdlist);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_data = (t_data *)malloc(sizeof(t_data));
	init_environ(env);
	while (1)
	{
		signal_handling(1);
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
