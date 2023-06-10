/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:27:40 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/10 15:51:42 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execve_part(t_cmd *cmdtable, char **path, char *tmp_env)
{
	char	*progname_with_sl;
	char	*prog_name_with_path;
	int		j;

	j = 0;
	tmp_env = my_get_env();
	path = ft_split(tmp_env + 5, ':');
	progname_with_sl = addslash(cmdtable->cmd[0]);
	while (path[j])
	{
		prog_name_with_path = ft_strjoin(path[j], progname_with_sl);
		if (access(prog_name_with_path, X_OK) == 0)
		{
			if (execute_2(cmdtable, prog_name_with_path) == 0)
			{
				free(prog_name_with_path);
				free(progname_with_sl);
				break ;
			}
		}
		else
			free(prog_name_with_path);
		j++;
	}
	free(progname_with_sl);
}


int	check_builtin_fork(t_cmd *cmdtable)
{
	if ((ft_strncmp(cmdtable->cmd[0], "echo", 5) == 0) && cmdtable->next)
		return (1);
	else if ((ft_strncmp(cmdtable->cmd[0], "pwd", 4) == 0) && cmdtable->next)
		return (1);
	else if ((ft_strncmp(cmdtable->cmd[0], "env", 4) == 0) && cmdtable->next)
		return (1);
	else if ((ft_strncmp(cmdtable->cmd[0], "export", 7) == 0) && \
	!cmdtable->cmd[1] && cmdtable->next)
		return (1);
	return (0);
}
