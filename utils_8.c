/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:22:17 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 02:58:07 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmdlist(t_cmdlist *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

// igno_0 = in, igno_1 = out
void	close_all_pipe(t_pipe *box, int num, int igno_0, int igno_1)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (box[i].fd[0] != igno_0 && box[i].fd[0] != igno_1)
			close(box[i].fd[0]);
		if (box[i].fd[1] != igno_1 && box[i].fd[1] != igno_0)
			close(box[i].fd[1]);
		i++;
	}
}

// pipe untill i error --> reverse close
static void	close_err_pipe(t_pipe *p, int i)
{
	if (i <= 0)
		return ;
	while (i)
	{
		close(p[i].fd[0]);
		close(p[i].fd[1]);
		i--;
	}
}

// num = num of cmd , NOT PIPE
t_pipe	*create_pipe(int num)
{
	t_pipe	*p;
	int		i;
	int		stat;

	stat = 1;
	p = (t_pipe *)malloc(sizeof(t_pipe) * num - 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < num - 1 && stat)
	{
		if (pipe(p[i].fd) == -1)
		{
			stat = 0;
			break ;
		}
		p->max = num;
		i++;
	}
	if (stat == 0)
		close_err_pipe(p, i);
	return (p);
}

// just open file
int	to_openheredoc(t_strcut *cmd, t_heredoc *hd)
{
	char	*fname;

	errno = 0;
	fname = ssp_strjoin("/tmp/hd_tmp-", ft_itoa(g_data->num), 0, 1);
	if (!fname)
		return (errno);
	while (cmd)
	{
		if (cmd->stat == 3)
		{
			if (which_redir(cmd->str) == 2)
			{
				hd->has_hd = 1;
				hd->fdhd = open(fname, O_RDONLY);
				if (hd->fdhd < 0)
					exit(err_msgexec(NULL, strerror(errno)));
				break ;
			}
			cmd = cmd->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
