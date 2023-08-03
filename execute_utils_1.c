/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 01:54:59 by bsirikam          #+#    #+#             */
/*   Updated: 2023/08/03 10:12:51 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_allfd(t_strcut *cmd, t_heredoc *hd, t_data *g_data, t_fd *ts_fd)
{
	int	lastin;

	hd->has_hd = 0;
	hd->fdhd = -2;
	lastin = find_lastinput(cmd);
	to_openheredoc(cmd, hd, g_data);
	if (lastin == 1 && hd->has_hd == 1)
		close(hd->fdhd);
	if (loop_openfile(cmd, &ts_fd->fdin, &ts_fd->fdout, g_data))
	{
		close_all_fd(&ts_fd->fdin, &ts_fd->fdout, hd);
		return (1);
	}
	if (ts_fd->fdin > 2 && lastin == 2)
		close(ts_fd->fdin);
	if (lastin == 2)
	{
		ts_fd->fdin = hd->fdhd;
		hd->fdhd = -2;
		hd->has_hd = 0;
	}
	return (0);
}

int	multi_exit(t_pipe *pipebox, pid_t *pids, int stat)
{
	free(pipebox);
	free(pids);
	return (stat);
}
