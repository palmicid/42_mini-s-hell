/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:41:49 by pruangde          #+#    #+#             */
/*   Updated: 2023/08/01 23:13:50 by bsirikam         ###   ########.fr       */
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
void	multi_execchild(t_strcut *cmd, t_pipe *p, int i, t_data *g_data)
{
	t_fd		*ts_fd;
	t_heredoc	hd;
	char		**cmdonly;

	g_data->num = i;
	ts_fd = (t_fd *)malloc(sizeof(t_fd));
	assign_pipe2fd(&ts_fd->fdin, &ts_fd->fdout, p, i);
	close_all_pipe(p, p->max - 1, ts_fd->fdin, ts_fd->fdout);
	if (init_allfd(cmd, &hd, g_data, ts_fd))
	{
		free(ts_fd);
		exit (g_data->exit_stat);
	}
	cmdonly = get_cmd(cmd);
	if (!cmdonly)
	{
		close_all_fd(&ts_fd->fdin, &ts_fd->fdout, &hd);
		free(ts_fd);
		exit(err_msgexec(NULL, strerror(errno)));
	}
	singlecmd_child(cmdonly, ts_fd->fdin, ts_fd->fdout, g_data);
	exit(EXIT_FAILURE);
}

int	multi_fork2exec(t_cmdlist *cmds, t_pipe *p, pid_t *pids, t_data *g_data)
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
			multi_execchild(cmds->cmd, p, i, g_data);
		i++;
		cmds = cmds->next;
	}
	return (0);
}
