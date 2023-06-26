/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:07:54 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/26 18:34:01 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_noarg(void)
{
	int		i;
	char	*msg;

	i = 0;
	while (g_data->env[i])
	{
		msg = ft_strjoin("declare -x ", get_key(g_data->env[i]));
		msg = ft_strjoin(msg, "=\"");
		msg = ft_strjoin(msg, getvalue(g_data->env[i], '='));
		msg = ft_strjoin(msg, "\"");
		ft_putendl_fd(msg, STDOUT_FILENO);
		free(msg);
		i++;
	}
}

char	*get_key(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (ft_substr(s, 0, i));
}

char	*remove_quote(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc((sizeof(char)) * (ft_strlen(cmd) - 1));
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i++;
		tmp[j] = cmd[i];
		j++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
