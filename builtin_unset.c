/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:49:53 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/29 09:05:54 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(s, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**copy_env(void)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (get_env_size() + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (g_data->env[i])
	{
		tmp[i] = ft_strdup(g_data->env[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	new_env(char *key, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data->env[i])
	{
		free(g_data->env[i]);
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(key, tmp[i], ft_strlen(key)) == 0)
			i++;
		if (!tmp[i])
			break ;
		g_data->env[j] = ft_strdup(tmp[i]);
		j++;
		i++;
	}
	g_data->env[j] = NULL;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
}

void	unset_env(char *key)
{
	int		i;
	int		env_size;
	char	*env_key;
	char	**tmp_env;

	i = 0;
	env_size = get_env_size();
	tmp_env = copy_env();
	while (i < env_size)
	{
		env_key = get_key(g_data->env[i]);
		if (ft_strncmp(env_key, key, ft_strlen(key)) == 0)
		{
			new_env(env_key, tmp_env);
			free(env_key);
			return ;
		}
		free(env_key);
		i++;
	}
}

void	ft_unset(t_cmdlist *cmdtable)
{
	int	i;
	int	j;

	if (ft_strncmp(cmdtable->cmd[0], "unset", 5) != 0 || !cmdtable->cmd[1])
		return ;
	if (ft_strncmp(cmdtable->cmd[0], "unset", 5) == 0 && cmdtable->cmd[1] && \
	cmdtable->cmd[1][0] == '-')
		return ;
	i = 1;
	while (cmdtable->cmd[i])
	{
		if (check_key(cmdtable->cmd[i]))
			return ;
		while (g_data->env[j])
		{
			if (ft_strncmp(cmdtable->cmd[i], g_data->env[j], \
			ft_strlen(cmdtable->cmd[i])) == 0)
			{
				unset_env(cmdtable->cmd[i]);
				break ;
			}
			j++;
		}
		i++;
		j = 0;
	}
}
