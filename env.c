/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/26 17:49:44 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environ(void)
{
	char	**tmp1;

	g_data->env = ft_splitdup(environ);
	tmp1 = g_data->env;
	g_data->env = environ;
	environ = tmp1;
}

void	end_environ(void)
{
	char	**tmp;

	tmp = g_data->env;
	g_data->env = environ;
	environ = tmp;
	ft_free_p2p_char(g_data->env);
	g_data->env = NULL;
}
