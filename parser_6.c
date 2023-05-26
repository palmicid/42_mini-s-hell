/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:31:11 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/26 16:21:56 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_strjoin(t_strcut *current, t_strcut **tmp)
{
	t_strcut	*curtmp;

	free(current->str);
	current->str = ft_calloc(1, 1);
	if (!current->str)
	{
		free_strcutlist(tmp);
		return (set_error(current));
	}
	curtmp = tmp[0];
	while (curtmp)
	{
		current->str = ssp_strjoin(current->str, curtmp->str, 1, 0);
		if (!current->str)
		{
			free_strcutlist(tmp);
			return (set_error(current));
		}
		curtmp = curtmp->next;
	}
}
