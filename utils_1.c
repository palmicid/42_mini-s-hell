/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:48:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/23 15:16:45 by pruangde         ###   ########.fr       */
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

int	find_charpos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
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
	printf("\n=======STRCUT_PRINT==========\n");
	while (ptr)
	{
		printf("stat = %d | str = %s\n", ptr->stat, ptr->str);
		ptr = ptr->next;
	}
	printf("=============================\n");
}
// 	-----------TEST-------------