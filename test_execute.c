#include "minishell.h"

static int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != ' '))
		i++;
	return (i);
}

static void	sp_putstrlen_fd(char *str, int fd)
{
	int	len;

	len = find_space(str);
	write(fd, str, len);
}

static void	do_error_exit(char *msg, char *str)
{
	if (msg && str)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		sp_putstrlen_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (str)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	exit(errno);
}

static void	p2p_free(char **ptr2d)
{
	int	i;

	i = 0;
	while (ptr2d[i])
	{
		free(ptr2d[i]);
		i++;
	}
	free(ptr2d);
	ptr2d = NULL;
}

static char	*sp_strtrim(char *s1, char *set)
{
	char	*strim;
	size_t	st;
	size_t	ed;

	if (!s1 || !set)
		return (NULL);
	st = 0;
	ed = ft_strlen(s1);
	while (ft_strchr(set, s1[st]) && s1[st])
		st++;
	while (ft_strchr(set, s1[ed]) && ed >= st)
		ed--;
	strim = ft_substr(s1, st, (ed - st) + 1);
	free(s1);
	return (strim);
}

static char	*search_path(char **split_path, char *prog_name, char *sl_progname)
{
	int		i;
	char	*path_program;

	i = 0;
	while (split_path[i])
	{
		if (i == 0)
			split_path[i] = sp_strtrim(split_path[i], "PATH=");
		path_program = ft_strjoin(split_path[i], sl_progname);
		if (access(path_program, F_OK) == 0)
		{
			p2p_free(split_path);
			free(prog_name);
			free(sl_progname);
			return (path_program);
		}
		free(path_program);
		i++;
	}
	p2p_free(split_path);
	free(sl_progname);
	if (access(prog_name, F_OK) != 0)
		errno = 127;
	return (prog_name);
}

static char	**path_split(void)
{
	int		i;
	char	**split_path;

	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))
			split_path = ft_split(environ[i], ':');
		i++;
	}
	return (split_path);
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
	split_path = path_split();
	prog2exe = search_path(split_path, prog_name, sl_progname);
	return (prog2exe);
}

static char	**cx_cmdpath(char **cmd)
{
	cmd[0] = findpath(cmd[0]);
	return (cmd);
}

static void	child_proc_cmd1(t_cmd *cmds)
{
	char	**cmd;

	cmd = cx_cmdpath(cmds->cmd);
	if (errno == 127)
	{
		p2p_free(cmd);
		do_error_exit("command not found", cmd[0]);
	}
	if (execve(cmd[0], cmd, environ) != 0)
	{
		p2p_free(cmd);
		do_error_exit(0, 0);
	}
}

// return exit code
int	to_execute(t_cmd *cmds)
{
	// int	err_stat = 0;
	pid_t	pid;
	// int	child_stat = 0;
	// int fd[2];
	// err_stat = 0;
	
	pid = fork();
	if (pid == 0)
		child_proc_cmd1(cmds);
	else
	{
		waitpid(pid, NULL, WNOHANG);
	}
	// if (pipe(fd) == -1)
	// 	do_error_exit(0, 0);
	// data->pid = fork();
	// if (data->pid == 0)
	// errno = err_stat;
	return (errno);
}