/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:52:30 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/28 14:08:15 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// ascii " == 34 , ' == 39 
// q_split convert str to link list 
// find ' or " in str if find mark pos then find another if not leave it
// " = 2, ' = 1, non = 0
t_strcut	*q_split(char *str)
{
	int	st;
	int	i;
	t_strcut	*strlist;

	strlist = NULL;
	i = 0;
	while (str[i])
	{
		st = i;
		while (str[i])
		{
			if (str[i] == 34 || str[i] == 39)
			{
				// find its pair + create list
				// and return i --> last pos for str
				// set mode 1 or 2 
				// if failed free inside the fx
				i = str_find_pair(str, i, &strlist);
				if (!strlist)
					return (NULL);
			}
			else 
			{
				// ++ until find ' " or \0
				// 

			}
		}
	}
	return (strlist);
}

// cmd_split split to arrey of struct list split by '|'

// find ' ' or " " if cannot find pair set all as a string
t_cmd	*str_split(char *str, t_cmd *table)
{
	t_strcut	*liststr;

	// find ' ' or " " cpy include ' ' ," "
	liststr = q_split(str);
	if (!liststr)
		return (NULL);
	// find $ << >> < > 
}
