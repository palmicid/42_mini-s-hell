
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:32:29 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/12 12:30:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_strcut	*next_findmetachar(t_strcut *head)
// {

// }

// find <<< or >>> if has = err
// err return 1 , ok return 0
int	find_metatriple(t_strcut *head)
{
	// 1 find < || >
	// if ' or " --> skip
	// 2 if < > find count if more than 2 err
}

// metachar == | < << > >>
// stat --> 0 = not cx, 1 = complete can skip
t_strcut	*meta_split(t_strcut *head)
{
	// t_strcut	*b4;
	// t_strcut	*now;
	// t_strcut	*aft;

	// now = head;
	// b4 = NULL;
	// aft = NULL;
	if (find_metaerr(head))
		return (free_strcutlist(&head));
	// while (now)
	// {

	// 	// reset now to head
	// 	now = next_findmetachar(head);
	// }
}
