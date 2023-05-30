/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 03:08:18 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 13:50:34 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// why int *i --> incase multiple space 
static t_strcut	*create_splst(char *str, int st, int *i, t_strcut *list)
{
	t_strcut	*last;

	if (!list)
	{
		list = (t_strcut *)malloc(sizeof(t_strcut));
		if (!list)
			return (NULL);
		list->str = ft_strndup(str + st, *i - st);
		list->stat = 0;
		list->next = NULL;
	}
	else
	{
		last = lastlist_strcut(list);
		last->next = (t_strcut *)malloc(sizeof(t_strcut));
		if (!last->next)
			return (free_strcutlist(&list));
		last->next->str = ft_strndup(str + st, *i - st);
		last->next->stat = 0;
		last->next->next = NULL;
	}
	*i = cont_char(str, *i, ' ');
	return (list);
}

static void	cx_dellast(t_strcut *list)
{
	t_strcut	*last;

	if (count_liststrcut(list) > 1)
	{
		last = list;
		while (last->next->next)
			last = last->next;
		if (ft_strlen(last->next->str) == 0)
			last->next = free_strcutlist(&(last->next));
	}
}

static int	sub_qsplit(char *str, int i, int *st, t_strcut **list)
{
	if (ft_isspace(str[i]))
	{
		list[0] = create_splst(str, *st, &i, list[0]);
		if (!list[0])
			return (-1);
		*st = i;
		i--;
	}
	else if ((str[i] == 34) || (str[i] == 39))
	{
		i = find_pair(str, i);
		if (i < 0)
			err_q_nopair();
	}
	return (i);
}

t_strcut	*qsp_split(char *str)
{
	int			i;
	int			st;
	t_strcut	*list;

	i = cont_char(str, 0, ' ');
	st = i;
	list = NULL;
	while (str[i] && i >= 0)
	{	
		i = sub_qsplit(str, i, &st, &list);
		if (i < 0)
			return (NULL);
		i++;
	}
	list = create_splst(str, st, &i, list);
	if (!list)
		return (NULL);
	cx_dellast(list);
	return (list);
}
