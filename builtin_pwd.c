/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:13:49 by bsirikam          #+#    #+#             */
/*   Updated: 2023/05/29 00:35:16 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (ft_substr(s, i + 1, ft_strlen(s)));
}

void	ft_pwd(t_cmd *cmdtable)
{
	char	*pwd;

	if (cmdtable->cmd[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	pwd = getvalue(getenv("PWD"));
	ft_putendl_fd(pwd, STDOUT_FILENO);
}