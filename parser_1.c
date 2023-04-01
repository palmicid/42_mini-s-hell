/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:52:30 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/02 02:05:32 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strcut	*q_split(char *str);

// find ' ' or " " if cannot find pair set all as a string
t_cmd	*str_split(char *str, t_cmd *table)
{
	t_strcut	*liststr;

	// find ' ' or " " cpy include ' ' ," "
	liststr = q_split(str);
	if (!liststr)
		return (NULL);
	// find $ << >> < >
	// FOR TEST ONLY !!!!
	(void)table;
	printf("test end\n");
	return (NULL);
	// FOR TEST ONLY !!!!

}

// ascii " == 34 , ' == 39 
// q_split convert str to link list 
// find ' or " in str if find mark pos then find another if not leave it
// " = 2, ' = 1, non = 0
static t_strcut	*q_split(char *str)
{
	int	i;
	t_strcut	*strlist;

	strlist = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = str_find_pair(str, i, &strlist);
			if (!strlist)
				return (NULL);
			i++;
		}
		else
		{
			i = strcut_nonq(str, i, &strlist);
			if (!strlist)
				return (NULL);
		}
	}
	return (strlist);
}

// cmd_split split to arrey of struct list split by '|'

