/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:52:31 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/28 12:34:44 by bsirikam         ###   ########.fr       */
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