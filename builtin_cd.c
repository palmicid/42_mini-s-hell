/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 23:51:57 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/04 22:57:18 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(char *pwd)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", "\"");
	oldpwd = ft_strjoin(oldpwd, pwd);
	oldpwd = ft_strjoin(oldpwd, "\"");
	return (oldpwd);
}

char	*get_pwd_now(char *pwd)
{
	char	*pwd_now;

	pwd_now = ft_strjoin("PWD=", "\"");
	pwd_now = ft_strjoin(pwd_now, pwd);
	pwd_now = ft_strjoin(pwd_now, "\"");
	return (pwd_now);
}

int	go_home(char *oldpwd)
{
	char	*pwd;

	if (chdir(my_getenv("HOME")) == -1)
		return (1);
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd);
	replace_env(pwd);
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

void	ft_cd(char **cmd)
{
	char	*oldpwd;

	oldpwd = get_old_pwd(getcwd(NULL, 0));
	if (is_home(cmd))
		go_home(oldpwd);
	else if (is_home_with_path(cmd))
		home_with_path(cmd, oldpwd);
	else
		normal_path(cmd, oldpwd);
}
