/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:34:55 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 02:58:38 by bsirikam         ###   ########.fr       */
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
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ret = onlycmd_dup(runner, ret);
	if (!ret)
		return (NULL);
	return (ret);
}

void	rec_heredoc(char *eof, t_heredoc *hd)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			err_heredoc_eof(eof);
			break ;
		}
		if (ft_strcmp(str, eof) == 0)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, hd->fdhd);
		free(str);
	}
	ft_putchar_fd('\0', hd->fdhd);
	close(hd->fdhd);
}

// return fd[0] close fd[1]
int	to_heredoc(t_strcut *list, t_heredoc *hd, int cmdnum)
{
	char	*fname;

	fname = ssp_strjoin("/tmp/hd_tmp-", ft_itoa(cmdnum), 0, 1);
	if (!fname)
		return (err_msgexec(NULL, strerror(errno)));
	while (list)
	{
		if (list->stat == 3 && which_redir(list->str) == 2)
		{
			if (hd->has_hd == 1)
				close(hd->fdhd);
			hd->has_hd = 1;
			hd->fdhd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (hd->fdhd < 0)
				return (err_msgexec(NULL, strerror(errno)));
			list = list->next;
			rec_heredoc(list->str, hd);
		}
		list = list->next;
	}
	return (0);
}
