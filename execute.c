/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:49:56 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/10 01:26:14 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

// void	builtin()

void	execute(t_cmd *cmdtable)
{
	char	**tmp_env;
	char	**path;
	int		i;
	int		j;
	char	**test;

	test = (char *[]){"ls", "-la", NULL};
	tmp_env = g_data->env;
	i = 0;
	(void)cmdtable;
	while (tmp_env[i])
	{
		j = 0;
		if (ft_strncmp("PATH", tmp_env[i], 4) == 0)
		{
			path = ft_split(tmp_env[i] + 5, ':');
			while (path[j])
			{
				printf("After join = %s\n", ft_strjoin(path[j], "/ls"));
				if (access(ft_strjoin(path[j], "/ls"), X_OK) == 0)
				{
					if (is_builtin("ls"))
						printf("builtin\n");
					else
						execve(ft_strjoin(path[j], "/ls"), test, NULL);
				}
				j++;
			}

		}
		i++;
	}
}