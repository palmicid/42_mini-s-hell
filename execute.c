/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:49:56 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/10 16:03:53 by bsirikam         ###   ########.fr       */
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
	if (ft_strncmp(cmdtable->cmd[0], "env", 3) == 0)
		ft_env(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "export", 5) == 0)
		ft_export(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "pwd", 3) == 0)
		ft_pwd(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "echo", 4) == 0)
		ft_echo(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "unset", 5) == 0)
		ft_unset(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "cd", 2) == 0)
		ft_cd(cmdtable);
	else if (ft_strncmp(cmdtable->cmd[0], "exit", 4) == 0)
		ft_exit(cmdtable);
}

char	*addslash(char *cmd)
{
	char	*sl_progname;

	if (cmd[0] == '/')
		sl_progname = ft_strjoin("", cmd);
	else
		sl_progname = ft_strjoin("/", cmd);
	return (sl_progname);
}

char	*my_get_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			return (ft_substr(environ[i], 5, ft_strlen(environ[i]) - 5));
		i++;
	}
	return (NULL);
}

void	execute(t_cmd *cmdtable)
{
	int		pid;
	int		fd[2];
	char	**path;
	char	*tmp_env;

	pid = -2;
	if (check_builtin_fork(cmdtable) || (!is_builtin(cmdtable->cmd[0]) \
	&& cmdtable->next))
	{
		pipe(fd);
		if (is_builtin(cmdtable->cmd[0]))
			pid = fork();
	}
	else if (!check_builtin_fork(cmdtable) && is_builtin(cmdtable->cmd[0]))
	{
		if (cmdtable->cmd[0] && is_builtin(cmdtable->cmd[0]))
		{
			builtin(cmdtable);
			return ;
		}
	}
	execve_part(cmdtable, path, tmp_env);
}
