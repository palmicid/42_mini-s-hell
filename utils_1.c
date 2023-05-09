/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:48:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/09 13:48:42 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strcut	*free_strcutlist(t_strcut **list)
{
	t_strcut	*head;
	t_strcut	*now;

	head = list[0];
	while (head)
	{	
		now = head;
		head = head->next;
		if (now->str)
			free(now->str);
		free(now);
	}
	now = NULL;
	list[0] = NULL;
	return (list[0]);
}

t_strcut	*free_strcut(t_strcut *tofree)
{
	if (tofree->str)
		free(tofree->str);
	free(tofree);
	tofree = NULL;
	return (tofree);
}

int	find_charpos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

t_strcut	*lastlist_strcut(t_strcut *list)
{
	t_strcut	*ret;

	ret = list;
	if (ret)
	{
		while (ret->next)
		{
			ret = ret->next;
		}
	}
	return (ret);
}

// skip same char return next pos to last c
int	cont_char(char *str, int i, char c)
{
	while (str[i] == c)
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
		printf("stat = %d | len = %zu | str = [%s]\n", ptr->stat, ft_strlen(ptr->str), ptr->str);
		ptr = ptr->next;
	}
	printf("=============================\n");
}
// 	-----------TEST-------------