/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:49:56 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/10 02:46:37 by bsirikam         ###   ########.fr       */
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

int	execute_2(t_cmd *cmdtable, char *pnamewp)
{
	int	pid;

	pid = fork();
	waitpid(pid, NULL, 0);
	if (pid == 0)
	{
		if (execve(pnamewp, cmdtable->cmd, NULL) != 0)
		{
			perror("execve");
			return (1);
		}
		return (0);
	}
	return (1);
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
	char	*tmp_env;
	char	**path;
	char	*progname_with_sl;
	int		j;
	char	*prog_name_with_path;

	j = 0;
	tmp_env = my_get_env();
	path = ft_split(tmp_env + 5, ':');
	if (cmdtable->cmd[0] && is_builtin(cmdtable->cmd[0]))
	{
		builtin(cmdtable);
		return ;
	}
	progname_with_sl = addslash(cmdtable->cmd[0]);
	while (path[j])
	{
		prog_name_with_path = ft_strjoin(path[j], progname_with_sl);
		if (access(prog_name_with_path, X_OK) == 0)
		{
			if (execute_2(cmdtable, prog_name_with_path) == 0)
			{
				free(prog_name_with_path);
				break ;
			}
		}
		else
			free(prog_name_with_path);
		j++;
	}
	free(progname_with_sl);
}
