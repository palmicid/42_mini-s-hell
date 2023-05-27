/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:56:05 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/28 01:27:38 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env()
{
	int i;

	i = 0;
	while (g_data->env[i])
	{
		printf("%s\n", g_data->env[i]);
		i++;
	}
}

void	ft_export_noarg()
{
	int	i;

	i = 0;
	while (g_data->env[i])
	{
		printf("declare -x %s\n", g_data->env[i]);
		i++;
	}
}

void	ft_export_witharg(char **cmd)
{
	(void)cmd;
	printf("export with arg\n");
}

void	ft_export(char **cmd)
{
	if (!cmd)
		ft_export_noarg();
	else
	{
		ft_export_witharg(cmd);
	}
}