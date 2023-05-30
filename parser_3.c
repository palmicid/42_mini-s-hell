/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:32:29 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 23:34:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find <<< or >>> if has = err
// err return 1 , ok return 0
// find '<' or '>' first and count if it more than 2
static int	find_metatriple(t_strcut *head)
{
	t_strcut	*ptr;
	int			i;

	ptr = head;
	while (ptr)
	{
		i = 0;
		while (ptr->str[i])
		{
			if (ptr->str[i] == 34 || ptr->str[i] == 39)
				i = find_pair(ptr->str, i) + 1;
			else if (ptr->str[i] == '<' || ptr->str[i] == '>')
			{
				if (count_samechar(ptr->str, i) > 2)
					return (1);
				i++;
			}
			else
				i++;
		}
		ptr = ptr->next;
	}
	return (0);
}

static int	cx_createdupsepmeta(char *str, int st, int pos, t_strcut *node)
{
	if (st == pos)
	{
		if ((str[pos] == str[pos + 1]) && (str[pos] != '|'))
			node->str = ft_strndup(str + st, 2);
		else
			node->str = ft_strndup(str + st, 1);
	}
	else
	{
		if (st < pos)
			node->str = ft_strndup(str + st, pos - st);
		else
			node->str = ft_strdup(str + st);
	}
	if (!(node->str))
		return (-1);
	node->stat = add_metastat(node->str);
	st += ft_strlen(node->str);
	return (st);
}

static t_strcut	*create_sepmeta(char *str, int pos)
{
	t_strcut	*ret;
	t_strcut	*creating;
	int			st;

	st = 0;
	ret = createnew_strcut();
	if (!ret)
		return (NULL);
	creating = ret;
	st = cx_createdupsepmeta(str, st, pos, creating);
	while (str[st])
	{
		creating->next = createnew_strcut();
		if (!(creating->next))
			return (free_strcutlist(&ret));
		creating = creating->next;
		st = cx_createdupsepmeta(str, st, pos, creating);
	}
	return (ret);
}

// if has metachar --> to sep
// if has metachar --> set thatlist of metachar to 2
// set stat for pipe to 4
// TMP == before now
// if fail free all
// find | < > but if <, > cx if next char is thesame
static void	sep_meta(t_strcut **head, t_strcut **now)
{
	t_strcut	*tmp;
	t_strcut	*aft;
	t_strcut	*ret;

	tmp = create_sepmeta(now[0]->str, find_metapos(now[0]->str));
	if (!tmp)
		head[0] = free_strcutlist(head);
	ret = new_nowsepmeta(tmp);
	if (now[0] == head[0])
	{
		head[0] = tmp;
		aft = lastlist_strcut(tmp);
		aft->next = now[0]->next;
	}
	else
	{
		aft = head[0];
		while (aft->next != now[0])
			aft = aft->next;
		aft->next = tmp;
		aft = lastlist_strcut(tmp);
		aft->next = now[0]->next;
	}
	now[0] = free_strcut(now[0]);
	now[0] = ret;
}

// continue meatachar == error
// metachar == | < << > >>
// stat --> 0 = not cx, 1 = complete can skip
// set stat = 1 if finish, 0 if not yet 
t_strcut	*meta_split(t_strcut *head)
{
	t_strcut	*now;

	if (find_metatriple(head))
	{
		err_redir();
		return (free_strcutlist(&head));
	}
	now = head;
	while (now)
	{
		if (now->stat == 0 || now->stat == 1)
		{
			if (find_metapos(now->str) >= 0)
			{
				sep_meta(&head, &now);
				if (!now)
					return (NULL);
			}
			else
				now->stat = 1;
		}
		now = now->next;
	}
	head = cx_meta_valid(head);
	return (head);
}
	// cx valid in fx if error free all and return NULL to head
