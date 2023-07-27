/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmpdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:15:27 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/27 22:39:35 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_tmpdir(t_cmdlist *cmd)
{
	pid_t	pid;
	int		stat;

	stat = 0;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		init_heredocfile(cmd);
	else
		waitpid(pid, &stat, 0);
	if (stat != 0)
	{
		end_environ();
		exit(EXIT_FAILURE);
	}
	return (stat);
}
