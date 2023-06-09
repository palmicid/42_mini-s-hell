/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 02:45:49 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/10 03:18:01 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_size(t_cmd *cmdtable)
{
	int	i;

	i = 0;
	while (cmdtable->cmd[i])
		i++;
	return (i);
}

int	check_arg1(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]) == 0 || cmd[i] == '-' || cmd[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmd *cmdtable)
{
	if (ft_strncmp(cmdtable->cmd[0], "exit", 5) == 0)
	{
		if (!cmdtable->cmd[1])
			exit(0);
		else if (cmd_size(cmdtable) > 2)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return ;
		}
		else
		{
			if (check_arg1(cmdtable->cmd[1]))
			{
				ft_putendl_fd("exit: exit number is invalid", 2);
				return ;
			}
			else
				exit(ft_atoi(cmdtable->cmd[1]) % 256);
		}
	}
}
