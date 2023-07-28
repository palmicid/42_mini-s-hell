/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:30:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/10 20:27:52 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find same char and return pair pos, if not return -1
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
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_samechar(char *str, int pos)
{
	int	count;
	int	i;

	count = 1;
	i = pos + 1;
	while ((str[pos] == str[i]) && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

// if found ret position of metachar, if not found ret -1
int	find_metapos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = find_pair(str, i);
			if (i < 0)
				return (-1);
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (i);
		i++;
	}
	return (-1);
}
