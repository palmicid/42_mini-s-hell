/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:48:58 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 01:53:18 by bsirikam         ###   ########.fr       */
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

void	echo_utils(char **cmd)
{
	char	*output;
	int		i;

	i = 1;
	while (cmd[i] && cmd[i + 1])
	{
		output = cutspace(cmd[i]);
		output = ft_strjoin(output, " ");
		ft_putstr_fd(output, STDOUT_FILENO);
		free(output);
		i++;
	}
	output = cutspace(cmd[i]);
	output = ft_strjoin(output, "\n");
	ft_putstr_fd(output, STDOUT_FILENO);
	free(output);
}

void	last_string(int i, char **cmd)
{
	char	*output;

	if (cmd[i])
	{
		output = cutspace(cmd[i]);
		ft_putstr_fd(output, STDOUT_FILENO);
		free(output);
	}
}

void	ft_echo(char **cmd)
{
	char	*output;
	int		i;

	i = 2;
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
			i++;
		while (cmd[i] && cmd[i + 1] && \
		ft_strncmp(cmd[i], "-n", 2) != 0)
		{
			output = cutspace(cmd[i]);
			output = ft_strjoin(output, " ");
			ft_putstr_fd(output, STDOUT_FILENO);
			free(output);
			i++;
		}
		last_string(i, cmd);
		return ;
	}
	echo_utils(cmd);
	return ;
}
