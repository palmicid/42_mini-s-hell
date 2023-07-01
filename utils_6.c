/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:34:55 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/01 14:21:32 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmdarg2alloc(t_strcut *runner)
{
	int	count;

	count = 0;
	while (runner)
	{
		if (runner->stat == 3)
			runner = runner->next;
		else
			count++;
		runner = runner->next;
	}
	return (count);
}

static char	**onlycmd_dup(t_strcut *runner, char **ret)
{
	int	i;

	i = 0;
	while (runner)
	{
		if (runner->stat == 3)
			runner = runner->next;
		else
		{
			ret[i] = ft_strdup(runner->str);
			i++;
		}
		runner = runner->next;
	}
	return (ret);
}

char	**get_cmd(t_strcut *head)
{
	char		**ret;
	int			count;
	t_strcut	*runner;


	runner = head;
	count = count_cmdarg2alloc(runner);
	ret = (char **)ft_calloc(count, sizeof(char *));
	if (!ret)
		return (NULL);
	ret = onlycmd_dup(runner, ret);
	if (!ret)
		return (NULL);
}

void	err_heredoc_eof(char *str)
{
	// bash: warning: here-document at line 1 delimited by end-of-file (wanted `blah')
	ft_putstr_fd("Minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2)
}

// return fd[0] close fd[1]
int	to_heredoc(t_strcut *list, t_heredoc *hd)
{
	hd->has_hd = 1;
	if (pipe(hd->fdhd) < 0)
		return (-1);
	while (list)
	{
		if (list->stat == 3 && which_redir(list->str) == 2)
		{
			
		}
	}
	
}

// mode 1 = input RDONLY , mode 3 = RDWR, 4 WR app
int	openfile(char *str, int *fd, int mode)
{
	if (*fd > 2)
		close(*fd);
	else if (mode == 1)
		*fd = open(str, O_RDONLY);
	else if (mode == 3)
		*fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (mode == 4)
		*fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (*fd < 0)
	{
		err_msgexec(str, strerror(errno));
		return (1);	
	}
	return (0);
}

int	fd_redir(t_strcut *cmd, int *fdin, int *fdout, t_heredoc *hd)
{
	if (which_redir(cmd) == 1)
		*fdin = openfile(cmd->next->str, fdin, NULL, 1);
	else if (which_redir(cmd) == 3)
		*fdin = openfile(cmd->next->str, fdout, NULL, 3);
	else if (which_redir(cmd) == 4)
		*fdin = openfile(cmd->next->str, fdout, NULL, 4);
	if (*fdin < 0 || *fdout < 0)
		return (1);
	return (0);
}
