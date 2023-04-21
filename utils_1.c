/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:48:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/18 21:20:57 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strcut	*free_strcutlist(t_strcut *list)
{
	t_strcut	*now;

	while (list)
	{	
		now = list;
		list = list->next;
		if (now->str)
			free(now->str);
		free(now);
	}
	now = NULL;
	return (list);
}

t_lstcmd	*free_listcmd(t_lstcmd *lstcmd)
{
	t_lstcmd	*now;

	now = lstcmd;
	while (lstcmd)
	{
		lstcmd = lstcmd->next;
		if (now->strcut)
			now->strcut = free_strcutlist(now->strcut);
		free(now);
	}
	return (NULL);
}

int	findpipe_count(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '|')
			i++;
		str++;
	}
	return (i);
}

int	find_charpos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

// return 0 if success , 1 if fail
int	pipe_addstr_tolist(t_strcut *fwd, t_strcut *aft, t_strcut *src)
{
	int	ppos;
	int	aftlen;

	ppos = find_charpos(src->str, '|');
	fwd->str = (char *)malloc(ppos + 1);
	if (!fwd->str)
		return (1);
	aftlen = ft_strlen(src->str + ppos);
	aft->str = (char *)malloc(aftlen + 1);
	if (!aft->str)
	{
		free(fwd->str);
		return (1);
	}
	fwd->str[ppos] = '\0';
	aft->str[aftlen] = '\0';
	ft_memcpy(fwd->str, src->str, ppos);
	ft_memcpy(aft->str, src->str + ppos + 1, aftlen);
	printf("====fwd %d = %s\n", ppos, fwd->str);
	printf("====aft %d = %s\n", aftlen, aft->str);
	return (0);
}


// 	-----------TEST-------------
void	test_print(t_lstcmd *head)
{
	t_strcut	*ptr;

	while (head)
	{
		ptr = head->strcut;
		while (ptr)
		{
			printf("no = %d | cmd = %s\n", head->cmd_no, ptr->str);
			ptr = ptr->next;
		}
		head = head->next;
	}
}

void	test_printstrcut(t_strcut *fwd)
{
	t_strcut	*ptr;
	ptr = fwd;
	printf("=============================\n");
	while (ptr)
	{
		printf("stat = %d | str = %s\n", ptr->stat, ptr->str);
		ptr = ptr->next;
	}
	printf("=============================\n");
}
// 	-----------TEST-------------