/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:12:54 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/09 21:05:36 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cx_after successfully create the list
int	add_metastat(char c)
{
	if (c == '|')
		return (4);
	else if (c == '<' || c == '>')
		return (2);
	return (1);
}

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
		if (ret->stat == 2 || ret->stat == 4)
			break ;
		ret = ret->next;
	}
	return (ret);
}

// if 2 not follow by 1 = error
// if 4 follow by 4 error
// cx syntax
