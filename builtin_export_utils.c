/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:07:54 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/29 00:08:16 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_noarg(void)
{
	int		i;
	char	*msg;

	i = 0;
	while (environ[i])
	{
		msg = ft_strjoin("declare -x ", environ[i]);
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
