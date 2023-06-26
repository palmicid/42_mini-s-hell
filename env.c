/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/26 18:51:07 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_environ(char **env)
{
	if (!g_data)
		exit(EXIT_FAILURE);
	g_data->env = ft_splitdup(env);
	if (!(g_data->env))
	{
		free(g_data);
		exit(EXIT_FAILURE);
	}
	g_data->strcmd = NULL;
	g_data->exit_stat = 0;
	return (0);
}

int	end_environ(void)
{
	ft_free_p2p_char(g_data->env);
	g_data->env = NULL;
	if (g_data->strcmd)
		free(g_data->strcmd);
	free(g_data);
	return (0);
}

char *my_getenv(char *str)
{
	char	*tofind;
	int		i;
	
	tofind = ft_strjoin(str, "=");
	if (!tofind)
		return (NULL);
	i = 0;
	while (g_data->env[i])
	{
		if (!ft_strncmp(tofind, g_data->env[i], ft_strlen(tofind)))
		{
			free(tofind);
			tofind = &g_data->env[i][find_charpos(g_data->env[i], '=') + 1];
			return (tofind);
		}
		i++;
	}
	free(tofind);
	return (NULL);
}
