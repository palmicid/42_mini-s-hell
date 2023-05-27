/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:12:54 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/27 17:34:35 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cx_after successfully create the list
int	add_metastat(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (4);
	else if ((ft_strncmp(str, "<", 2) == 0) || (ft_strncmp(str, ">", 2) == 0))
		return (3);
	else if ((ft_strncmp(str, "<<", 3) == 0) || (ft_strncmp(str, ">>", 3) == 0))
		return (3);
	return (1);
}

// find the list before the now
t_strcut	*search_liststrcut(t_strcut *head, t_strcut *now)
{
	t_strcut	*tofind;

	if (head == now)
		return (head);
	tofind = head;
	while (tofind->next != now && tofind)
		tofind = tofind->next;
	return (tofind);
}

t_strcut	*new_nowsepmeta(t_strcut *tmphd)
{
	t_strcut	*ret;

	ret = tmphd;
	while (ret)
	{
		if (ret->stat == 3 || ret->stat == 4)
			break ;
		ret = ret->next;
	}
	return (ret);
}

// if 3 not follow by 1 = error
// if 4 follow by 4 error
// cx syntax
t_strcut	*cx_meta_valid(t_strcut *head)
{
	t_strcut	*runner;

	runner = head;
	while (runner->next != NULL)
	{
		if (runner->stat == 4 || runner->stat == 3)
		{
			if (runner->stat == runner->next->stat)
				return (inside_cxmetavalid(&head, runner->next->str));
			if (runner->stat == 3 && runner->next->stat == 4)
				return (inside_cxmetavalid(&head, runner->next->str));
		}
		runner = runner->next;
	}
	if (((runner->stat == 3) || runner->stat == 4))
		return (inside_cxmetavalid(&head, "newline"));
	return (head);
}

void	restat_normal(t_strcut *head)
{
	while (head)
	{
		if (head->stat == 1)
			head->stat = 0;
		head = head->next;
	}
}
