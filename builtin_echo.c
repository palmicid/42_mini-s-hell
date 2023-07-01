/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:48:58 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/29 09:05:32 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cutspace(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && isspace(s[i]))
		i++;
	j = i;
	while (s[j] && !isspace(s[j]))
	{
		j++;
	}
	return (ft_substr(s, i, j));
}

void	echo_utils(t_cmdlist *cmdtable)
{
	char	*output;
	int		i;

	i = 1;
	while (cmdtable->cmd[i] && cmdtable->cmd[i + 1])
	{
		output = cutspace(cmdtable->cmd[i]);
		output = ft_strjoin(output, " ");
		ft_putstr_fd(output, STDOUT_FILENO);
		free(output);
		i++;
	}
	output = cutspace(cmdtable->cmd[i]);
	output = ft_strjoin(output, "\n");
	ft_putstr_fd(output, STDOUT_FILENO);
	free(output);
}

void	last_string(int i, t_cmdlist *cmdtable)
{
	char	*output;

	if (cmdtable->cmd[i])
	{
		output = cutspace(cmdtable->cmd[i]);
		ft_putstr_fd(output, STDOUT_FILENO);
		free(output);
	}
}

void	ft_echo(t_cmdlist *cmdtable)
{
	char	*output;
	int		i;

	i = 2;
	if (ft_strncmp(cmdtable->cmd[1], "-n", 2) == 0)
	{
		while (cmdtable->cmd[i] && ft_strncmp(cmdtable->cmd[i], "-n", 2) == 0)
			i++;
		while (cmdtable->cmd[i] && cmdtable->cmd[i + 1] && \
		ft_strncmp(cmdtable->cmd[i], "-n", 2) != 0)
		{
			output = cutspace(cmdtable->cmd[i]);
			output = ft_strjoin(output, " ");
			ft_putstr_fd(output, STDOUT_FILENO);
			free(output);
			i++;
		}
		last_string(i, cmdtable);
		return ;
	}
	echo_utils(cmdtable);
	return ;
}