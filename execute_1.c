/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:04:35 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/02 12:00:26 by pruangde         ###   ########.fr       */
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
// init all and find redirect
int	init_allfd(t_strcut *cmd, int *fdin, int *fdout, t_heredoc *hd)
{
	// int	lastin;
	
	// *fdin = 0;
	// *fdout = 1;
	// hd->has_hd = 0;
	// lastin = 0;
	(void) fdin;
	(void) fdout;
	// Loop heredoc;
	to_heredoc(cmd, hd);
	// Loop open file
	return (0);
	// while (cmd)
	// {
	// 	if (cmd->stat == 3)
	// 	{
	// 		if (fd_redir(cmd, fdin, fdout, hd))
	// 			return (1);
	// 		cmd = cmd->next;
	// 	}
	// 	cmd = cmd->next;
	// }
}

static int	one_exec(t_cmdlist *cmd)
{
	// char		**cmdonly;
	int			fdin;
	int			fdout;
	t_heredoc	heredoc;
	
	if (init_allfd(cmd->cmd, &fdin, &fdout, &heredoc))
		return (g_data->exit_stat);
	// cmdonly = get_cmd(cmd->cmd);
	// if must run in parent (no output && no input)
	// no dup2 b4 fork
	// cmdonly = get_cmdlist(cmd);
	return (1);
	// if (!cmdonly)
	// {
	// 	// close all open fd;
	// 	return (0);
	// }
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
