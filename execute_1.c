/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:04:35 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/03 09:40:32 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	back2normal(int fdin, int fdout, t_heredoc *hd)
// {
// 	if (fdin > 2)
// 		dup2(STDIN_FILENO, fdin);
// 	if (fdout > 2)
// 		dup2(STDOUT_FILENO, fdout);
	
// }

// lastin == cx if last re in == fd || heredoc
// init all and find redirect
int	init_allfd(t_strcut *cmd, int *fdin, int *fdout, t_heredoc *hd)
{
	int	lastin;
	
	*fdin = 0;
	*fdout = 1;
	hd->has_hd = 0;
	lastin = find_lastinput(cmd);
	to_heredoc(cmd, hd);
	if (lastin == 1 && hd->has_hd == 1)
		close(hd->fdhd[0]);
	if (loop_openfile(cmd, fdin, fdout))
	{
		close_all_fd(fdin, fdout, hd);
		return (1);
	}
	if (*fdin > 2 && lastin == 2)
		close(*fdin);
	return (0);
}

static int	one_exec(t_cmdlist *cmd)
{
	// char		**cmdonly;
	int			fdin;
	int			fdout;
	t_heredoc	heredoc;
	
	if (init_allfd(cmd->cmd, &fdin, &fdout, &heredoc))
		return (g_data->exit_stat);
	if (!cmdonly)
	{
		close_all_fd(&fdin, &fdout, &heredoc);
		return (1);
	}

	// if (cx_bltin_parent(cmdonly))
	// 	exec_bltin(cmdonly);
	// cx if sp bltin


}

void	to_execute(t_cmdlist *cmd)
{
	if (cmd->next == NULL)
		g_data->exit_stat = one_exec(cmd);
	// else
	// 	g_data->exit_stat = multi_exec(cmd);
}
