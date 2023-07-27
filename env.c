/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 02:57:51 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	plus_shelllevel(void)
{
	int		i;
	int		lvl;
	char	*newlvl;

	i = 0;
	while (g_data->env[i])
	{
		if (ft_strncmp(g_data->env[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(my_getenv("SHLVL"));
			lvl++;
			newlvl = ssp_strjoin("SHLVL=", ft_itoa(lvl), 0, 1);
			if (!newlvl)
				return ;
			free(g_data->env[i]);
			g_data->env[i] = newlvl;
		}
		i++;
	}
}

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
	g_data->tmp_dir = ft_strdup("/tmp/minishell");
	g_data->strcmd = NULL;
	g_data->exit_stat = 0;
	g_data->num = 0;
	plus_shelllevel();
	return (0);
}

int	end_environ(void)
{
	ft_free_p2p_char(g_data->env);
	g_data->env = NULL;
	if (g_data->strcmd)
		free(g_data->strcmd);
	free(g_data->tmp_dir);
	free(g_data);
	return (0);
}

char	*my_getenv(char *str)
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
