/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:48:58 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 03:51:43 by bsirikam         ###   ########.fr       */
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

void	echo(char **str, int start)
{
	int	count;

	count = count_element_p2p(str);
	if (str[start])
		ft_putstr_fd(str[start], 1);
	start++;
	while (start < count)
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(str[start], 1);
		start++;
	}
}

void	ft_echo(char **cmd)
{
	if (cmd[1] == NULL)
		return ;
	if (cmd[1][0] == '-')
	{
		if (ft_strncmp(cmd[1], "-n", 3) == 0)
		{
			if (cmd[2] == NULL)
				return ;
			echo(cmd, 2);
			return ;
		}
	}
	echo(cmd, 1);
	ft_putchar_fd('\n', 1);
	return ;
}
