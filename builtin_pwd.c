/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:13:49 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/29 09:05:50 by pruangde         ###   ########.fr       */
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

void	ft_pwd(t_cmdlist *cmdtable)
{
	char	*pwd;

	if (cmdtable->cmd[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("Error\n", STDERR_FILENO);
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
}
