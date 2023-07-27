/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:43:09 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/23 01:33:05 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_cmdlist *cmdtable)
{
	t_cmdlist		*tmp;
	int				i;
	char			*name;
	t_heredoc		*heredoc_list;
	t_heredoc		*new_list;
	t_heredoc		*tmpdoc;
	char			*line;

	tmp = cmdtable;
	heredoc_list = NULL;
	i = 0;
	while (tmp->cmd)
	{
		if (ft_strncmp(tmp->cmd->str, "<<", 3) == 0)
		{
			name = hash_name(tmp->cmd->next->str);
			new_list = add_new(name);
			add_last_here_doc(&heredoc_list, new_list);
			free(name);
		}
		tmp->cmd = tmp->cmd->next;
	}
	tmpdoc = heredoc_list;
	while (tmpdoc)
	{
		tmpdoc->fd = open(tmpdoc->str, O_RDWR | O_CREAT | O_APPEND, 06444);
		tmpdoc = tmpdoc->next;
	}
	tmpdoc = heredoc_list;
	while (tmpdoc)
	{
		close(tmpdoc->fd);
		tmpdoc = tmpdoc->next;
	}
	tmpdoc = heredoc_list;
	while (tmpdoc)
	{
		unlink(tmpdoc->str);
		tmpdoc = tmpdoc->next;
	}
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
	}
	// printl(heredoc_list);
	exit(0);
}