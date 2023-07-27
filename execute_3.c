/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 03:17:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 03:04:54 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_close(int in, int out)
{
	g_data->exit_stat = 0;
	if (in != 0)
	{
		if (dup2(in, STDIN_FILENO) < 0)
			g_data->exit_stat = errno;
		close(in);
	}
	if (out != 1)
	{
		if (dup2(out, STDOUT_FILENO) < 0)
			g_data->exit_stat = errno;
		close(out);
	}
	return (g_data->exit_stat);
}

// to_built has exit in itself
//
void	singlecmd_child(char **cmd, int fdin, int fdout)
{
	if (dup_close(fdin, fdout))
		exit(errno);
	if (cx_isbltin(cmd[0]))
		to_builtin(cmd);
	cmd = cx_cmdpath(cmd);
	if (errno != 0)
		exit(errno);
	if (execve(cmd[0], cmd, g_data->env) == -1)
		exit(errno);
}
// copy pipex to exe 5 - 6
// exe 4 for multiple
