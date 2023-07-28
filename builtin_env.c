/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:52:31 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 15:02:05 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_error(char *s)
{
	char	*msg;

	msg = ft_strdup("Minishell >> ");
	if (s)
	{
		msg = ft_strjoin(msg, "env : ");
		msg = ft_strjoin(msg, s);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	free(msg);
}

void	ft_env(char **cmd, t_data *g_data)
{
	int		i;

	i = 0;
	if (cmd[0] && cmd[1])
	{
		env_error("too many arguments");
		return ;
	}
	while (g_data->env[i])
	{
		ft_putendl_fd(g_data->env[i], STDOUT_FILENO);
		i++;
	}
}

int	validate_env(char *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (env[i] == '=')
			count++;
		if (env[i] && (env[i] == '\"' || env[i] == '\''))
			count++;
		i++;
	}
	if (count == 3)
		return (1);
	return (0);
}

void	replace_env(char *env, t_data *g_data)
{
	int		i;
	char	*key;

	i = 0;
	key = get_key(env);
	while (g_data->env[i])
	{
		if (ft_strncmp(key, g_data->env[i], ft_strlen(key)) == 0)
		{
			free(g_data->env[i]);
			g_data->env[i] = ft_strdup(env);
			free(key);
			return ;
		}
		i++;
	}
}
