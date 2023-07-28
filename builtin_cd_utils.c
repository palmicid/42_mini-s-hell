/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:19 by bsirikam          #+#    #+#             */
/*   Updated: 2023/07/28 13:51:18 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_home_with_path(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && \
	ft_strncmp(cmd[1], "~", 2) != 0 && \
	cmd[1][0] == '~' && cmd[1][1] != '\0')
		return (1);
	return (0);
}

int	home_with_path(char **cmd, char *oldpwd, t_data *g_data)
{
	char	*cd;
	char	*pwd;

	cd = ft_strjoin(my_getenv("HOME", g_data), ft_substr(cmd[1], 1, \
		ft_strlen(cmd[1])));
	if (chdir(cd) == -1)
	{
		cd = ft_strjoin("cd: ", cd);
		cd = ft_strjoin(cd, ": No such file or directory\n");
		ft_putstr_fd(cd, 2);
		free(cd);
		return (1);
	}
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd, g_data);
	replace_env(pwd, g_data);
	free(oldpwd);
	free(pwd);
	free(cd);
	return (0);
}

int	normal_path(char **cmd, char *oldpwd, t_data *g_data)
{
	char	*pwd;
	char	*cd;

	if (chdir(cmd[1]) == -1)
	{
		cd = ft_strjoin("cd: ", cmd[1]);
		cd = ft_strjoin(cd, ": No such file or directory\n");
		ft_putstr_fd(cd, 2);
		free(cd);
		return (1);
	}
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd, g_data);
	replace_env(pwd, g_data);
	free(oldpwd);
	free(pwd);
	return (0);
}
