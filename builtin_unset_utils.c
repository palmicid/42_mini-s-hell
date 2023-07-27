/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 02:53:47 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 02:56:32 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_incorrect(char **cmd)
{
	if (!cmd[1])
		return (1);
	if (cmd[1] && cmd[1][0] == '-')
		return (1);
	return (0);
}
