/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:04:35 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/27 22:29:47 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	back2normal(int fdin, int fdout, t_heredoc *hd)
{
	if (fdin > 2)
		dup2(STDIN_FILENO, fdin);
	if (fdout > 2)
		dup2(STDOUT_FILENO, fdout);
	
}
// init all and find redirect
int	init_allfd(t_cmd *cmd, int *fdin, int *fdout, t_heredoc *hd)
{
	*fdin = -1;
	*fdout = -1;
	hd->has_hd = 0;

	
}

int	one_exec(t_cmd *cmd)
{
	char		**cmdonly;
	int			fdin;
	int			fdout;
	t_heredoc	heredoc;
	
	if (init_allfd(cmd, &fdin, &fdout, &heredoc))
		return (g_data->exit_stat);
	cmdonly = get_cmd(cmd);
	if (!cmdonly)
	{
		// close all open fd;
		return (0);
	}
	if (cx_bltin_parent(cmdonly))
		exec_bltin(cmdonly);
	// cx if sp bltin


}

void	to_execute(t_cmd *cmd)
{
	if (cmd->next == NULL)
		g_data->exit_stat = one_exec(cmd);
	else
		g_data->exit_stat = multi_exec(cmd);
}
