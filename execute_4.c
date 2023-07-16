/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:41:49 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/15 02:27:44 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait4fork(pid_t *pids, int num)
{
	int	i;
	int	stat;

	stat = 0;
	i = 0;
	while (i < num && pids[i] > 0)
	{
		waitpid(pids[i], &stat, 0);
		i++;
	}
	return (stat);
}

void	assign_pipe2fd(int *in, int *out, t_pipe *p, int i)
{
	if (i == 0)
		*in = 0;
	else
		*in = p[i - 1].fd[0];
	if (i == (p->max - 1))
		*out = 1;
	else
		*out = p[i].fd[1];
}

// for multi pipe
// i = cmd number .. ,
void	multi_execchild(t_strcut *cmd, t_pipe *p, int i)
{
	int			fdin;
	int			fdout;
	t_heredoc	hd;
	char		**cmdonly;
	
	g_data->num = i;
	assign_pipe2fd(&fdin, &fdout, p, i);
	close_all_pipe(p, p->max - 1, fdin, fdout);
	if (init_allfd(cmd, &fdin, &fdout, &hd))
		exit (g_data->exit_stat);
	cmdonly = get_cmd(cmd);
	if (!cmdonly)
	{
		close_all_fd(&fdin, &fdout, &hd);
		exit(err_msgexec(NULL, strerror(errno)));
	}
	singlecmd_child(cmdonly, fdin, fdout);
	exit(EXIT_FAILURE);
}

int	multi_fork2exec(t_cmdlist *cmds, t_pipe *p, pid_t *pids)
{
	int	i;
	int	ncmd;

	i = 0;
	ncmd = p->max;
	while (i < ncmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (errno);
		else if (pids[i] == 0)
			multi_execchild(cmds->cmd, p, i);
		i++;
		cmds = cmds->next;
	}
	return (0);
}
