/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:51:57 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 13:51:57 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(char *pwd)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", pwd);
	return (oldpwd);
}

char	*get_pwd_now(char *pwd)
{
	char	*pwd_now;

	pwd_now = ft_strjoin("PWD=", pwd);
	return (pwd_now);
}

int	go_home(char *oldpwd, t_data *g_data)
{
	char	*pwd;

	if (chdir(my_getenv("HOME", g_data)) == -1)
		return (1);
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd, g_data);
	replace_env(pwd, g_data);
	free(oldpwd);
	free(pwd);
	return (0);
}

int	is_home(char **cmd)
{
	if ((ft_strncmp(cmd[0], "cd", 2) == 0 && !cmd[1]) || \
		(ft_strncmp(cmd[0], "cd", 2) == 0 && \
		ft_strncmp(cmd[1], "~", 2) == 0))
		return (1);
	return (0);
}

void	ft_cd(char **cmd, t_data *g_data)
{
	char	*oldpwd;

	oldpwd = get_old_pwd(getcwd(NULL, 0));
	if (is_home(cmd))
		go_home(oldpwd, g_data);
	else if (is_home_with_path(cmd))
		home_with_path(cmd, oldpwd, g_data);
	else
		normal_path(cmd, oldpwd, g_data);
}
