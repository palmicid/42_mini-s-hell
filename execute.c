/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:49:56 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/26 02:04:16 by bsirikam         ###   ########.fr       */
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

void	builtin(t_cmd *cmdtable)
{
	// (void)cmdtable;
	t_cmd	*tmp;
	tmp = cmdtable;
	// char	test[] = "export";
	while (tmp)
	{
		if (ft_strncmp(*tmp->cmd, "env", 3) == 0)
			ft_env();
		else if (ft_strncmp(*tmp->cmd, "export", 5) == 0)
		{
			tmp = tmp->next;
			ft_export(tmp->cmd);
		}
	}
}

void	execute(t_cmd *cmdtable)
{
	char	**tmp_env;
	char	**path;
	int		i;
	int		j;
	char	**test;

	// test = (char *[]){"ls", "-la", NULL};
	tmp_env = g_data->env;
	i = 0;
	// (void)cmdtable;
	// cmdtable = malloc(sizeof(t_cmd));
	// cmdtable->cmd = malloc(sizeof(char *) * 2);
	// cmdtable->cmd[0] = ft_strdup("export");
	// cmdtable->next = NULL;
	while (tmp_env[i])
	{
		j = 0;
		if (ft_strncmp("PATH", tmp_env[i], 4) == 0)
		{
			path = ft_split(tmp_env[i] + 5, ':');
			while (path[j])
			{
				if (access(ft_strjoin(path[j], "/ls"), X_OK) == 0)
				{
					if (is_builtin("env"))
						builtin(cmdtable);
					else
					{
						execve(ft_strjoin(path[j], "/ls"), test, NULL);
						exit(EXIT_SUCCESS);
					}
				}
				j++;
			}

		}
		i++;
	}
}