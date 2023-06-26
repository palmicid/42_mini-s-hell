/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:52:31 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/26 18:33:55 by pruangde         ###   ########.fr       */
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

void	ft_env(t_cmd *cmdtable)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmdtable;
	if (tmp->cmd[0] && tmp->cmd[1])
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

void	replace_env(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = get_key(env);
	if (validate_env(env) == 0)
		return ;
	env = remove_quote(env);
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
