/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:56:05 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 04:37:28 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isalready(char *cmd)
{
	char	*cmd_without_value;
	int		i;

	i = 0;
	cmd_without_value = get_key(cmd);
	while (g_data->env[i])
	{
		if (ft_strncmp(cmd_without_value, g_data->env[i], \
		ft_strlen(cmd_without_value)) == 0)
		{
			free(cmd_without_value);
			return (0);
		}
		i++;
	}
	return (1);
}

int	find_tmp_size(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i])
		i++;
	return (i);
}

void	replace_environment(char **tmp)
{
	int	i;
	int	tmp_size;

	i = 0;
	tmp_size = find_tmp_size(tmp);
	while (g_data->env[i])
	{
		free(g_data->env[i]);
		i++;
	}
	free(g_data->env);
	g_data->env = malloc(sizeof(char *) * (tmp_size + 1));
	i = 0;
	while (tmp[i])
	{
		g_data->env[i] = ft_strdup(tmp[i]);
		i++;
	}
	g_data->env[i] = NULL;
	ft_free_p2p_char(tmp);
}

void	ft_export_witharg(char **cmd)
{
	int		env_size;
	char	**tmp;
	int		i;

	if (isalready(cmd[1]) == 0)
	{
		replace_envexport(cmd[1]);
		return ;
	}
	i = 0;
	env_size = get_env_size();
	tmp = malloc(sizeof(char *) * (env_size + 2));
	while (g_data->env[i])
	{
		tmp[i] = ft_strdup(g_data->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(cmd[1]);
	tmp[i + 1] = NULL;
	replace_environment(tmp);
}

void	ft_export(char **cmd)
{
	if (!cmd[1])
		ft_export_noarg();
	else
		ft_export_witharg(cmd);
}
