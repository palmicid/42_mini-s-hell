/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:55:03 by bsirikam          #+#    #+#             */
/*   Updated: 2023/08/03 09:57:25 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nocmdonly(t_fd *ts_fd, t_heredoc *heredoc)
{
	close_all_fd(&ts_fd->fdin, &ts_fd->fdout, heredoc);
	free(ts_fd);
	return (1);
}

int	initfd_fail(t_fd *ts_fd, t_data *g_data)
{
	free(ts_fd);
	return (g_data->exit_stat);
}

int	bltparent_exit(char **cmdonly, t_fd *ts_fd, t_data *g_data)
{
	free(ts_fd);
	return (exec_bltin_parent(cmdonly, g_data) || \
	ft_free_p2p_char(cmdonly));
}
