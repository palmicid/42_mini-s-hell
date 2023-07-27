/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:48:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 03:04:42 by bsirikam         ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_strcut	*lastlist_strcut(t_strcut *list)
{
	t_strcut	*ret;

	ret = list;
	if (ret != NULL)
	{
		while (ret->next != NULL)
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
