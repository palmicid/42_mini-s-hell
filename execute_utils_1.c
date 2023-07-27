/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 01:54:59 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 01:56:31 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_allfd(t_strcut *cmd, int *fdin, int *fdout, t_heredoc *hd)
{
	int	lastin;

	hd->has_hd = 0;
	hd->fdhd = -2;
	lastin = find_lastinput(cmd);
	to_openheredoc(cmd, hd);
	if (lastin == 1 && hd->has_hd == 1)
		close(hd->fdhd);
	if (loop_openfile(cmd, fdin, fdout))
	{
		close_all_fd(fdin, fdout, hd);
		return (1);
	}
	if (*fdin > 2 && lastin == 2)
		close(*fdin);
	if (lastin == 2)
	{
		*fdin = hd->fdhd;
		hd->fdhd = -2;
		hd->has_hd = 0;
	}
	return (0);
}
