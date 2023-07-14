/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:34:55 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/15 02:18:40 by pruangde         ###   ########.fr       */
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
		ft_putendl_fd(str, hd->fdhd[1]);
		free(str);
	}
	ft_putchar_fd('\0', hd->fdhd[1]);
	close(hd->fdhd[1]);
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
			if (hd->has_hd == 1)
				close(hd->fdhd[0]);
			hd->has_hd = 1;
			if (pipe(hd->fdhd) < 0)
				return (-1);
			list = list->next;
			rec_heredoc(list->str, hd);
		}
		list = list->next;
	}
	return 0;
}
