/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:56:05 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/29 00:10:48 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isalready(char *cmd)
{
	char	*cmd_without_value;
	int		i;

	i = 0;
	cmd_without_value = get_key(cmd);
	while (environ[i])
	{
		if (ft_strncmp(cmd_without_value, environ[i], \
		ft_strlen(cmd_without_value)) == 0)
		{
			free(cmd_without_value);
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_env_size(void)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

void	replace_environ(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(environ[i]);
		environ[i] = ft_strdup(tmp[i]);
		i++;
	}
	environ[i] = NULL;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
}

void	ft_export_witharg(t_cmd *cmdtable)
{
	int		env_size;
	char	**tmp;
	int		i;

	if (isalready(cmdtable->cmd[1]) == 0)
	{
		replace_env(cmdtable->cmd[1]);
		return ;
	}
	i = 0;
	env_size = get_env_size();
	tmp = malloc(sizeof(char *) * (env_size + 1));
	while (environ[i])
	{
		tmp[i] = ft_strdup(environ[i]);
		i++;
	}
	tmp[i] = ft_strdup(cmdtable->cmd[1]);
	tmp[i + 1] = NULL;
	replace_environ(tmp);
}

void	ft_export(t_cmd *cmdtable)
{
	t_cmd	*tmp;

	tmp = cmdtable;
	if (!tmp->cmd[1])
		ft_export_noarg();
	else
		ft_export_witharg(tmp);
}
