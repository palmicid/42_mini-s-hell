/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:04:35 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 15:37:05 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_bltin_parent(char **cmd, t_data *g_data)
{
	errno = 0;
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd(cmd, g_data);
	else if (ft_strcmp("export", cmd[0]) == 0)
		ft_export(cmd, g_data);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		ft_exit(cmd);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		ft_unset(cmd, g_data);
	return (errno);
}

// lastin == cx if last re in == fd || heredoc
// init all and find redirect

static int	single_execwithfork(char **cmdonly, int fdin, int fdout, t_data *g_data)
{
	int	pid;
	int	exit_stat;
	int	chld_stat;

	pid = fork();
	if (pid == -1)
		return (err_msgexec(NULL, strerror(errno)));
	if (pid == 0)
		singlecmd_child(cmdonly, fdin, fdout, g_data);
	else
	{
		waitpid(pid, &chld_stat, 0);
		if (WIFEXITED(chld_stat))
		{
			exit_stat = WEXITSTATUS(chld_stat);
			g_data->exit_stat = exit_stat;
			return (1);
		}
	}
	return (0);
}

static int	one_exec(t_cmdlist *cmd, t_data *g_data)
{
	char		**cmdonly;
	int			fdin;
	int			fdout;
	t_heredoc	heredoc;

	fdin = 0;
	fdout = 1;
	if (to_heredoc(cmd->cmd, &heredoc, 0))
		return (EXIT_FAILURE);
	if (init_allfd(cmd->cmd, &fdin, &fdout, &heredoc, g_data))
		return (g_data->exit_stat);
	cmdonly = get_cmd(cmd->cmd);
	if (!cmdonly)
	{
		close_all_fd(&fdin, &fdout, &heredoc);
		return (1);
	}
	if (cx_bltin_parent(cmdonly))
		return (exec_bltin_parent(cmdonly, g_data) || ft_free_p2p_char(cmdonly));
	else if (single_execwithfork(cmdonly, fdin, fdout, g_data))
		;
	cmdonly = ft_free_p2p_char(cmdonly);
	return (g_data->exit_stat);
}

static int	multi_exec(t_cmdlist *cmd, t_data *g_data)
{
	int		ncmd;
	t_pipe	*pipebox;
	int		stat;
	pid_t	*pids;

	stat = 0;
	ncmd = count_cmdlist(cmd);
	init_before_fork(cmd, ncmd, &pipebox, &pids, g_data);
	if (errno != 0)
		return (errno);
	stat = multi_fork2exec(cmd, pipebox, pids, g_data);
	if (stat)
		err_msgexec(NULL, strerror(stat));
	close_all_pipe(pipebox, ncmd - 1, -1, -1);
	stat = wait4fork(pids, ncmd);
	free(pipebox);
	free(pids);
	return (stat);
}

void	to_execute(t_cmdlist *cmd, t_data *g_data)
{
	signal_handling(2);
	errno = 0;
	if (cmd->next == NULL)
		g_data->exit_stat = one_exec(cmd, g_data);
	else
		g_data->exit_stat = multi_exec(cmd, g_data);
}
