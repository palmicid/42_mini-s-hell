/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:42:28 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/12 12:03:19 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_path(char **split_path, char *sl_progname)
{
	int		i;
	char	*path_program;

	i = 0;
	while (split_path[i])
	{
		path_program = ft_strjoin(split_path[i], sl_progname);
		if (access(path_program, X_OK) == 0)
		{
			ft_free_p2p_char(split_path);
			free(sl_progname);
			return (path_program);
		}
		free(path_program);
		i++;
	}
	split_path = ft_free_p2p_char(split_path);
	free(sl_progname);
	sl_progname = NULL;
	errno = 127;
	return (sl_progname);
}

static char	*findnadd_slash(char *prog_name)
{
	char	*sl_progname;

	if (prog_name[0] == '/')
		sl_progname = ft_strjoin("", prog_name);
	else
		sl_progname = ft_strjoin("/", prog_name);
	return (sl_progname);
}

static char	*findpath(char *prog_name)
{
	char	**split_path;
	char	*sl_progname;
	char	*prog2exe;

	sl_progname = findnadd_slash(prog_name);
	if (!sl_progname)
	{
		err_msgexec(NULL, strerror(errno));
		return (NULL);
	}
	split_path = ft_split(my_getenv("PATH"), ':');
	if (!split_path)
	{
		free(sl_progname);
		err_msgexec(NULL, strerror(errno));
		return (NULL);
	}
	prog2exe = search_path(split_path, sl_progname);
	if (!prog2exe)
	{
		err_msgexec(prog_name, "command not found");
		return (NULL);
	}
	return (prog2exe);
}

char	**cx_cmdpath(char **cmd)
{
	char	*ret_cmd;

	if (access(cmd[0], X_OK) != -1)
		return (cmd);
	ret_cmd = findpath(cmd[0]);
	if (ret_cmd)
	{
		errno = 0;
		free(cmd[0]);
		cmd[0] = ret_cmd;
	}
	return (cmd);
}
