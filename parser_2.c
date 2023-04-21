/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 03:08:18 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/05 14:27:52 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strcut	*find_laststrcut(t_strcut *strlist);
static void		addstat_strcut(t_strcut *last, int ed);

// str[i] --> first, strlist == to create list
int	str_find_pair(char *str, int i, t_strcut **strlist)
{
	int			st;
	t_strcut	*last;

	st = i++;
	while ((str[i] != str[st]) && str[i])
		i++;
	last = find_laststrcut(strlist[0]);
	if (!last)
	{
		last = (t_strcut *)malloc(sizeof(t_strcut));
		strlist[0] = last;
	}
	else
	{
		last->next = (t_strcut *)malloc(sizeof(t_strcut));
		last = last->next;
	}
	if (!last)
		exit(errno);
	last->str = ft_strndup(&str[st], (i - st) + 1);	
	addstat_strcut(last, (i - st));
	return (i);
}

static t_strcut	*find_laststrcut(t_strcut *strlist)
{
	t_strcut	*last;

	last = strlist;
	if (last == NULL)
		;
	else
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
	}
	return (last);
}

static void	addstat_strcut(t_strcut *last, int ed)
{
	if (last->str[0] == last->str[ed])
	{
		if (last->str[0] == 34)
			last->stat = 2;
		else if (last->str[0] == 39)
			last->stat = 1;
	}
	else
		last->stat = 0;
}

int	strcut_nonq(char *str, int i, t_strcut **strlist)
{
	int			st;
	t_strcut	*last;

	st = i++;
	while (((str[i] != 34) && (str[i] != 39)) && str[i])
		i++;
	last = find_laststrcut(strlist[0]);
	if (!last)
	{
		last = (t_strcut *)malloc(sizeof(t_strcut));
		strlist[0] = last;
	}
	else
	{
		last->next = (t_strcut *)malloc(sizeof(t_strcut));
		last = last->next;
	}
	last->str = ft_strndup(&str[st], i - st);
	addstat_strcut(last, (i - st) - 1);
	return (i);
}
