/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:30:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/18 15:07:02 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strcut	*splitp_error(t_strcut *leftcmd, t_strcut **tofree)
{
	t_strcut	*ptr;

	if (tofree[0])
		free(tofree[0]);
	leftcmd->stat = -1;
	ptr = leftcmd->next;
	while (ptr)
	{
		ptr->stat = -1;
		ptr = ptr->next;
	}
	return (leftcmd);
}
