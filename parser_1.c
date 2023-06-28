/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:52:30 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/28 23:48:59 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*sep_commandlist(t_cmd *head, t_strcut *run)
{
	t_cmd	*cmd;

	cmd = head;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd->next)
		return (free_cmdlist(&head));
	cmd = cmd->next;
	cmd->cmd = run->next;
	cmd->next = NULL;
	return (head);
}

static void	remove_pipe_fromlist(t_cmd *head)
{
	t_cmd		*cmdlst;
	t_strcut	*strlst;

	cmdlst = head;
	while (cmdlst)
	{
		strlst = cmdlst->cmd;
		while (strlst && strlst->next)
		{
			if (strlst->next->stat == 4)
			{
				free(strlst->next->str);
				free(strlst->next);
				strlst->next = NULL;
			}
			strlst = strlst->next;
		}
		cmdlst = cmdlst->next;
	}
}

static t_cmd *fusion_and_sepcmd(t_strcut *liststr)
{
	t_cmd		*head;
	t_strcut	*runstr;

	head = (t_cmd *)malloc(sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->cmd = liststr;
	head->next = NULL;
	runstr = liststr;
	while (runstr)
	{
		if (runstr->stat == 4)
		{
			head = sep_commandlist(head, runstr);
			if (!head)
				return (NULL);
		}
		runstr = runstr->next;
	}
	remove_pipe_fromlist(head);
	return (head);
}

// find ' ' or " " if cannot find pair set all as a string
t_cmd	*str_split(char *str, t_data *data)
{
	t_strcut	*liststr;
	t_cmd		*listcmd;

	liststr = qsp_split(str);
	if (!liststr)
		return (NULL);
	liststr = meta_split(liststr);
	if (!liststr)
		return (NULL);
	liststr = remove_q_xpand(liststr, data);
	if (!liststr)
		return (NULL);
	// test_printstrcut(liststr);
	listcmd = fusion_and_sepcmd(liststr);
	if (!listcmd)
		return (NULL);
	return (listcmd);
}
