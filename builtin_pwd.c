/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:13:49 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/31 00:09:43 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (ft_substr(s, i + 1, ft_strlen(s)));
}

void	ft_pwd(t_cmd *cmdtable)
{
	char	*pwd;
	int		i;

	if (cmdtable->cmd[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PWD=", 4) == 0)
		{
			pwd = getvalue(environ[i], '=');
			ft_putendl_fd(pwd, STDOUT_FILENO);
			free(pwd);
			return ;
		}
		i++;
	}
}