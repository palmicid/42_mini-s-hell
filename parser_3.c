
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:32:29 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/12 12:30:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if nothing after | or strlen last == 0 --> not run only front one
// find how many pipe first an malloc all list before add list
// if findpipe_malloc found multiple pipe also return NULL;
// cx multiple pipe in findpipe_malloc
// if any malloc fail just ret null lst str will be freed outside
t_lstcmd	*pipe_split(t_lstcmd *headcmd ,t_strcut *lststr)
{
	headcmd = findpipe_malloc(lststr);
	if (!headcmd)
		return (NULL);
	headcmd->cmd_no = 0;
	headcmd->strcut = lststr;
	headcmd = sep_cmd(headcmd);
	// 	-----------TEST-------------
	test_print(headcmd);
	// 	-----------TEST-------------
	if (!headcmd)
		exit(EXIT_FAILURE);
	return (headcmd);
}

// if malloc fail free all and ret NULL
t_lstcmd	*sep_cmd(t_lstcmd *hdcmd)
{
	t_lstcmd	*nowcmd;
	t_strcut	*left_str;
	int			num;

	num = 0;
	nowcmd = hdcmd;
	nowcmd->cmd_no = num++;
	left_str = hdcmd->strcut;
	while (left_str && (left_str->stat != -1))
	{
		
		while (left_str->stat == 0 && (left_str->stat != -1) && left_str)
		{
			while (ft_strchr(left_str->str, '|') && left_str->stat != -1)
			{
				left_str = new_listcmd(&nowcmd, left_str);
				if (left_str->stat == -1)
					return (free_listcmd(hdcmd));
				nowcmd->cmd_no = num;
				test_print(hdcmd);
				num++;
			}
			left_str = left_str->next;
		}
		left_str = left_str->next;
	}
	return (hdcmd);
}

t_strcut	*new_listcmd(t_lstcmd **nowcmd, t_strcut *leftstr)
{
	t_strcut	*tmp2free;
	t_strcut	*fwdstr;
	t_strcut	*aftstr;

	tmp2free = leftstr;
	leftstr = leftstr->next;
	fwdstr = (t_strcut *)malloc(sizeof(t_strcut));
	if (!fwdstr)
		return (splitp_error(leftstr, &fwdstr));
	nowcmd[0]->strcut = fwdstr;
	aftstr = (t_strcut *)malloc(sizeof(t_strcut));
	if (!aftstr)
	{
		fwdstr = free_strcutlist(fwdstr);
		return (splitp_error(leftstr, &aftstr));
	}
	nowcmd[0] = nowcmd[0]->next;
	fwdstr->stat = 0;
	aftstr->stat = 0;
	if (pipe_addstr_tolist(fwdstr, aftstr, tmp2free))
		return (free_strcutlist(leftstr));
	aftstr->next = leftstr;
	test_printstrcut(aftstr);
	tmp2free->next = NULL;
	free_strcutlist(tmp2free);
	return (aftstr);
}

// cx if str has multiple pipe and not separate in str or sep but nothing between

t_lstcmd	*findpipe_malloc(t_strcut *lststr)
{
	int			num_pipe;
	t_lstcmd	*hdcmd;

	hdcmd = NULL;
	num_pipe = 0;
	while (lststr)
	{
		if (lststr->stat == 0)
			num_pipe += findpipe_count(lststr->str);
		lststr = lststr->next;
	}
	hdcmd = listcmd_malloc(hdcmd, num_pipe);
	if (!hdcmd)
		return (NULL);
	return (hdcmd);
}

// if malloc fail free head
t_lstcmd	*listcmd_malloc(t_lstcmd *hdcmd, int np)
{
	t_lstcmd	*last;
	int			num_cmd;

	hdcmd = (t_lstcmd *)malloc(sizeof(t_lstcmd));
	if (!hdcmd)
		return (NULL);
	last = hdcmd;
	last->next = NULL;
	num_cmd = 0;
	while (num_cmd < np)
	{
		last->next = (t_lstcmd *)malloc(sizeof(t_lstcmd));
		if (!last)
			return (free_listcmd(hdcmd));
		last = last->next;
		last->next = NULL;
		num_cmd++;
	}
	return (hdcmd);
}
