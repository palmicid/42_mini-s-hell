/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:49:56 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/26 18:34:45 by pruangde         ###   ########.fr       */
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
	while (g_data->env[i])
	{
		if (ft_strncmp(g_data->env[i], "PATH=", 5) == 0)
			return (ft_substr(g_data->env[i], 5, ft_strlen(g_data->env[i]) - 5));
		i++;
	}
	return (NULL);
}

int		lst_cmd_size(t_cmd *cmdtable)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	if (!cmdtable)
		return (0);
	tmp = cmdtable;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_pipe(t_cmd *cmdtable)
{
	t_pipe	*pipe_s;
	t_cmd	*tmp;
	int		size_fd;
	int		i;

	pipe_s = malloc(sizeof(t_pipe));
	size_fd = (lst_cmd_size(cmdtable) - 1) * 2;
	pipe_s->size_fd = size_fd;
	pipe_s->fd = malloc(sizeof(int) * size_fd);
	i = 0;
	while (i < (size_fd / 2))
	{
		if (pipe(pipe_s->fd + i * 2) < 0)
			ft_putstr_fd("pipe error\n", 2);
		i++;
	}
	tmp = cmdtable;
	while (tmp)
	{
		tmp->pipe = pipe_s;
		tmp = tmp->next;
	}
}

int	is_redirect_sign(char *s)
{
	if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	return (0);
}

char	*hash_name(char *filename)
{
	int		i;
	int		table_size;
	int		c;
	char	*hash_name;

	i = 0;
	table_size = ft_strlen(filename);
	hash_name = malloc(sizeof(char) * table_size + 1);
	while (filename[i])
	{
		c = filename[i];
		hash_name[i] = c + i;
		i++;
	}
	hash_name[i] = '\0';
	return (hash_name);
}

void	heredoc(t_cmd *cmdtable)
{
	t_cmd	*tmp;
	int		i;
	char	*name;

	tmp = cmdtable;
	i = 0;
	while (tmp->cmd[i])
	{
		if (ft_strncmp(tmp->cmd[i], "<<", 3) == 0)
		{
			name = hash_name(tmp->cmd[i + 1]);
			printf("Hello heredoc\n");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	execute(t_cmd *cmdtable)
{
	int		pid;
	int		fd[2];
	char	**path;
	char	*tmp_env;
	// pid = -2;
	// if (check_builtin_fork(cmdtable) || (!is_builtin(cmdtable->cmd[0]) \
	// && cmdtable->next))
	// {
	// 	pipe(fd);
	// 	if (is_builtin(cmdtable->cmd[0]))
	// 		pid = fork();
	// }
	// else if (!check_builtin_fork(cmdtable) && is_builtin(cmdtable->cmd[0]))
	// {
	// 	if (cmdtable->cmd[0] && is_builtin(cmdtable->cmd[0]))
	// 	{
	// 		builtin(cmdtable);
	// 		return ;
	// 	}
	// }
	if (lst_cmd_size(cmdtable) != 1)
		init_pipe(cmdtable);
	heredoc(cmdtable);
	exit(EXIT_SUCCESS);
	execve_part(cmdtable, path, tmp_env);
}
