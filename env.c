/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 17:21:16 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_environ(t_data *data)
{
	char	**tmp1;

	if (!data)
		exit(EXIT_FAILURE);
	data->env = ft_splitdup(environ);
	if (!(data->env))
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	tmp1 = data->env;
	data->env = environ;
	environ = tmp1;
	data->exit_stat = 0;
	return (0);
}

int	end_environ(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	data->env = environ;
	environ = tmp;
	ft_free_p2p_char(data->env);
	data->env = NULL;
	free(data);
	return (0);
}
