/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 00:00:14 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 15:33:25 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mode 1 = input RDONLY , mode 3 = RDWR, 4 WR app
void	openfile(char *str, int *fd, int mode, t_data *g_data)
{
	if (*fd > 2)
		close(*fd);
	if (mode == 1)
		*fd = open(str, O_RDONLY);
	else if (mode == 3)
		*fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (mode == 4)
		*fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (*fd < 0)
		g_data->exit_stat = errno;
}

int	fd_redir(t_strcut *cmd, int *fdin, int *fdout, t_data *g_data)
{
	if (which_redir(cmd->str) == 1)
		openfile(cmd->next->str, fdin, 1, g_data);
	else if (which_redir(cmd->str) == 3)
		openfile(cmd->next->str, fdout, 3, g_data);
	else if (which_redir(cmd->str) == 4)
		openfile(cmd->next->str, fdout, 4, g_data);
	if (*fdin < 0 || *fdout < 0)
		return (1);
	return (0);
}

// find if last input heredoc(2) or file(1) return -1 if not found
int	find_lastinput(t_strcut *cmd)
{
	int	lastin;

	lastin = -1;
	while (cmd)
	{
		if (cmd->stat == 3)
		{
			if (which_redir(cmd->str) == 1)
				lastin = 1;
			else if (which_redir(cmd->str) == 2)
				lastin = 2;
			cmd = cmd->next;
		}
		cmd = cmd->next;
	}
	return (lastin);
}

int	loop_openfile(t_strcut *cmd, int *fdin, int *fdout, t_data *g_data)
{
	while (cmd)
	{
		if (cmd->stat == 3)
		{
			if (fd_redir(cmd, fdin, fdout, g_data))
			{
				err_msgexec(cmd->next->str, strerror(errno));
				return (1);
			}
			cmd = cmd->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	close_all_fd(int *fdin, int *fdout, t_heredoc *hd)
{
	if (*fdin > 2)
		close(*fdin);
	if (*fdout > 2)
		close(*fdout);
	if (hd->has_hd)
		close(hd->fdhd);
}
