/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/28 22:19:00 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environ(t_data *data)
{
	char	**tmp1;

	data->env = ft_splitdup(environ);
	tmp1 = data->env;
	data->env = environ;
	environ = tmp1;
}

void	end_environ(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	data->env = environ;
	environ = tmp;
	ft_free_p2p_char(data->env);
	data->env = NULL;
}
