/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:52:31 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/28 23:34:07 by bsirikam         ###   ########.fr       */
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
	while (environ[i])
	{
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
}

void	replace_env(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = get_key(env);
	while (environ[i])
	{
		if (ft_strncmp(key, environ[i], ft_strlen(key)) == 0)
		{
			free(environ[i]);
			environ[i] = ft_strdup(env);
			free(key);
			return ;
		}
		i++;
	}
}