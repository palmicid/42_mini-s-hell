/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:52:30 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/09 21:49:51 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find ' ' or " " if cannot find pair set all as a string
t_cmd	*str_split(char *str, t_cmd *table)
{
	t_strcut	*liststr;
	// t_lstcmd	*listcmd;
	// t_cmd		*tabcmd;

	// listcmd = NULL;
	// find space 
	liststr = qsp_split(str);
	if (!liststr)
		return (NULL);
	liststr = meta_split(liststr);
	if (!liststr)
		return (NULL);
	test_printstrcut(liststr);
	// listcmd = pipe_split(listcmd, liststr);
	// if (!listcmd)
	// {
	// 	free_strcutlist(&liststr);
	// 	return (NULL);
	// }
	// run cx str find space to separate cmd
	// find $ << >> < >

	// FOR TEST ONLY !!!!
	(void)table;
	if (liststr)
		liststr = free_strcutlist(&liststr);
	return (NULL);
	// FOR TEST ONLY !!!!

}

// ascii " == 34 , ' == 39 
// q_split convert str to link list 
// find ' or " in str if find mark pos then find another if not leave it
// " = 2, ' = 1, non = 0

// cmd_split split to arrey of struct list split by '|'

