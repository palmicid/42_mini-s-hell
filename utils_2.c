/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:30:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/08 01:29:29 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find same char and return pair pos
// if not return -1
int	find_pair(char *str, int i)
{
	int	st;

	st = i;
	i++;
	while (str[i])
	{
		if (str[st] == str[i])
			return (i);
		i++;
	}
	return (-1);
}

int	count_liststrcut(t_strcut *list)
{
	t_strcut	*tmp;
	int			count;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

// space == 1, non-space == 0
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

// int	find_meta(char c)
// {
// 	if (c == '|' || c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

