/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:35:55 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 17:00:55 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strcut	*create_lst(char *str, int st, int *i, t_strcut *list)
{
	t_strcut	*last;

	if (!list)
	{
		list = (t_strcut *)malloc(sizeof(t_strcut));
		if (!list)
			return (NULL);
		list->str = ft_strndup(str + st, (*i + 1) - st);
		list->stat = 0;
		list->next = NULL;
	}
	else
	{
		last = lastlist_strcut(list);
		last->next = (t_strcut *)malloc(sizeof(t_strcut));
		if (!last->next)
			return (free_strcutlist(&list));
		last->next->str = ft_strndup(str + st, (*i + 1) - st);
		last->next->stat = 0;
		last->next->next = NULL;
	}
	return (list);
}

static int	to_subqsplit(char *str, int i, int *st, t_strcut **list)
{
	if ((str[i] == 34) || (str[i] == 39))
	{
		i = find_pair(str, i);
		list[0] = create_lst(str, *st, &i, list[0]);
		if (!list[0])
			return (-1);
	}
	else
	{
		i = next_i_qsplit(str, i);
		list[0] = create_lst(str, *st, &i, list[0]);
		if (!list[0])
			return (-1);
	}
	*st = i + 1;
	i++;
	return (i);
}

// create list if faile NULL
// plus add stat 0 nothing, 1 ' , 2 "
static t_strcut	*creat_q_strcutlst(char *str)
{
	t_strcut	*tmp;
	t_strcut	*ret;
	int			i;
	int			st;

	i = 0;
	st = i;
	ret = NULL;
	while (str[i] && i >= 0)
	{	
		i = to_subqsplit(str, i, &st, &ret);
		if (i < 0)
			return (NULL);
	}
	remove_q(ret);
	tmp = ret;
	while (tmp)
	{
		if (tmp->stat == -1)
			return (free_strcutlist(&ret));
		tmp = tmp->next;
	}
	return (ret);
}

// 1. spitstr if no q dont split -> strlist
// 2. remove outside q if strlen == 0 ,left it as its be set stat
// 3. find if any $ and convert follow stat setting
// 4. join all str together --> free old and replace by newone
// run in str if find
static void	remove_qproc(t_strcut *current, t_data *data)
{
	t_strcut	*tmp;

	tmp = creat_q_strcutlst(current->str);
	if (!tmp)
		return (set_error(current));
	expand_var(tmp, data);
	if (tmp->stat == -1)
	{
		set_error(current);
		free_strcutlist(&tmp);
		return ;
	}
	lst_strjoin(current, &tmp);
	free_strcutlist(&tmp);
}

// remove q and then search for VAR in env 
// if not donothing just del it 
// if have q in str split it remove q and expand
// bef == list before ptr, aft == list after ptr if any
// remove q and expand
t_strcut	*remove_q_xpand(t_strcut *head, t_data *data)
{
	t_strcut	*ptr;

	restat_normal(head);
	ptr = head;
	while (ptr)
	{
		if (ptr->stat == 0)
		{
			if (find_q_doll(ptr->str))
			{
				remove_qproc(ptr, data);
				if (ptr->stat == -1)
					return (free_strcutlist(&head));
			}
			ptr->stat = 1;
		}
		ptr = ptr->next;
	}
	return (head);
}
