/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:52:30 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/26 21:22:33 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strcut	*find_nextcmd(t_strcut *tofind)
{
	t_strcut	*list;

	list = tofind;
	while (list)
	{
		if (list->stat == 4)
			return (list->next);
		list = list->next;
	}
	return (list);
}

// count how many to malloc sep by pipe
static	int	count_strarray(t_strcut *cur)
{
	int	count;

	count = 0;
	while (cur->stat != 4)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

static char	**cmd_fusion(t_strcut *curlst)
{
	int			index;
	int			count;
	char		**strarr;
	t_strcut	*curstr;

	index = 0;
	curstr = curlst;
	count = count_strarray(curstr);
	strarr = (char **)malloc(sizeof(char *) * (count + 1));
	strarr[count] = NULL;
	while (index <= count)
	{
		strarr[index] = ft_strdup(curstr->str);
		if (!strarr[index])
		{
			ft_free_p2p_char(strarr);
			return (NULL);
		}
		index++;
		curstr = curstr->next;
	}
	return (strarr);
}

static t_cmd	*fusion_and_sepcmd(t_strcut *liststr)
{
	t_cmd		*headcmd;
	t_cmd		*nowcmd;
	t_strcut	*curstr;

	curstr = liststr;
	headcmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!headcmd)
		return (NULL);
	headcmd->cmd = cmd_fusion(curstr);
	if (!headcmd->cmd)
		return (free_cmdlist(headcmd));
	curstr = find_nextcmd(curstr);
	nowcmd = headcmd;
	while (curstr)
	{
		nowcmd->next = (t_cmd *)malloc(sizeof(t_cmd));
		if (!nowcmd->next)
			return (free_cmdlist(headcmd));
		nowcmd = nowcmd->next;
		nowcmd->cmd = cmd_fusion(curstr);
		if (!nowcmd->cmd)
			return (free_cmdlist(headcmd));
		curstr = find_nextcmd(curstr);
	}
	return (headcmd);
}

// find ' ' or " " if cannot find pair set all as a string
t_cmd	*str_split(char *str)
{
	t_strcut	*liststr;
	t_cmd		*listcmd;

	liststr = qsp_split(str);
	if (!liststr)
		return (NULL);
	liststr = meta_split(liststr);
	if (!liststr)
		return (NULL);
	liststr = remove_q_xpand(liststr);
	if (!liststr)
		return (NULL);
	listcmd = fusion_and_sepcmd(liststr);
	if (!listcmd)
		errno = 1;
	if (liststr)
		liststr = free_strcutlist(&liststr);
	
	test_printstrcut(liststr);
	test_print(listcmd);
	
	return (listcmd);

}

// ascii " == 34 , ' == 39 
// q_split convert str to link list 
// find ' or " in str if find mark pos then find another if not leave it
// " = 2, ' = 1, non = 0

// cmd_split split to arrey of struct list split by '|'

