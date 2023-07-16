/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmpdir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:15:27 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/16 09:51:09 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this is a child
static void	my_mkdir(void)
{
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * 4);
	if (!cmd)
		exit(EXIT_FAILURE);
	cmd[0] = ft_strdup("mkdir");
	cmd[1] = ft_strdup("-p");
	cmd[2] = ft_strdup("/tmp/minishell")
}

void	create_tmpdir(void)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if(pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		my_mkdir();
	else
		waitpid(pid, &stat, 0);
	if (stat != 0)
	{
		end_environ();
		exit(EXIT_FAILURE);
	}
}
