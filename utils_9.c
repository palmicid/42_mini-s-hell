/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:53:02 by pruangde          #+#    #+#             */
/*   Updated: 2023/08/03 09:42:23 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredocfile(t_cmdlist *cmds, t_data *g_data)
{
	int			i;
	t_heredoc	hd;

	g_data->pid = fork();
	signal_handling(2);
	i = 0;
	if (g_data->pid == 0)
	{
		while (cmds)
		{
			errno = 0;
			hd.fdhd = -2;
			hd.has_hd = 0;
			to_heredoc(cmds->cmd, &hd, i);
			if (errno != 0)
				return ;
			i++;
			cmds = cmds->next;
		}
		exit (EXIT_SUCCESS);
	}
	else if (g_data->pid > 0)
		waitpid(g_data->pid, &i, 0);
	g_data->pid = 0;
}

void	init_before_fork(int n, t_pipe **pb, pid_t **ps)
{
	errno = 0;
	if (!ps[0])
		return ;
	if (errno != 0)
	{
		free(ps[0]);
		close_all_pipe(pb[0], n, -1, -1);
		free(pb[0]);
		return ;
	}
	return ;
}
