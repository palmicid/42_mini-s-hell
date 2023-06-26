/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:56:15 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/26 18:34:27 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(void)
{
	int	i;

	i = 0;
	while (g_data->env[i])
		i++;
	return (i);
}
