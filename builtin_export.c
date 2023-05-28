/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:56:05 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/28 15:50:03 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_export_noarg()
{
	int	i;
	char	*msg;

	i = 0;
	while (g_data->env[i])
	{
		msg = ft_strjoin("declare -x ", g_data->env[i]);
		ft_putendl_fd(msg, STDOUT_FILENO);
		free(msg);
		i++;
	}
}

void	ft_export_witharg(t_cmd *cmdtable)
{
	while (cmdtable)
	{
	}
}

void	ft_export(t_cmd *cmdtable)
{
	t_cmd	*tmp;

	tmp = cmdtable;
	if (!tmp->cmd[1])
		ft_export_noarg();
	else
	{
		ft_export_witharg(tmp);
	}
}