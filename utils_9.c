/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:53:02 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/27 22:45:23 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_heredocfile(t_cmdlist *cmds)
{
	int	i;
	t_heredoc	hd;

	i = 0;
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
}

void	init_before_fork(t_cmdlist *cmds, int n, t_pipe **pb, pid_t **ps)
{
	errno = 0;
	ps[0] = (pid_t *)ft_calloc(sizeof(pid_t) ,n);
	if (!ps[0])
		return ;
	pb[0] = create_pipe(n);
	if (!pb[0])
	{
		free(ps);
		return ;
	}
	init_heredocfile(cmds);
	if (errno != 0)
	{
		free(ps[0]);
		close_all_pipe(pb[0], n, -1, -1);
		free(pb[0]);
		return ;
	}
	return ;
}
