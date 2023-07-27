/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:07:54 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 00:43:22 by bsirikam         ###   ########.fr       */
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
	int		n;
	char	*tmp;

	i = 0;
	j = 0;
	n = ft_strlen(cmd) - 2;
	tmp = malloc((sizeof(char)) * (n + 1));
	while (cmd[i] != '\0' && cmd[i] != '\'' && cmd[i] == '\"')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i++;
		tmp[j] = cmd[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
