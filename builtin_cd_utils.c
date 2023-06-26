/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:19 by bsirikam          #+#    #+#             */
/*   Updated: 2023/06/26 15:54:37 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_home_with_path(t_cmd *cmdtable)
{
	if (ft_strncmp(cmdtable->cmd[0], "cd", 2) == 0 && \
	ft_strncmp(cmdtable->cmd[1], "~", 2) != 0 && \
	cmdtable->cmd[1][0] == '~' && cmdtable->cmd[1][1] != '\0')
		return (1);
	return (0);
}

int	home_with_path(t_cmd *cmdtable, char *oldpwd)
{
	char	*cd;
	char	*pwd;

	cd = ft_strjoin(my_getenv("HOME"), ft_substr(cmdtable->cmd[1], 1, \
		ft_strlen(cmdtable->cmd[1])));
	if (chdir(cd) == -1)
	{
		cd = ft_strjoin("cd: ", cd);
		cd = ft_strjoin(cd, ": No such file or directory\n");
		ft_putstr_fd(cd, 2);
		free(cd);
		return (1);
	}
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd);
	replace_env(pwd);
	free(oldpwd);
	free(pwd);
	free(cd);
	return (0);
}

int	normal_path(t_cmd *cmdtable, char *oldpwd)
{
	char	*pwd;
	char	*cd;

	if (chdir(cmdtable->cmd[1]) == -1)
	{
		cd = ft_strjoin("cd: ", cmdtable->cmd[1]);
		cd = ft_strjoin(cd, ": No such file or directory\n");
		ft_putstr_fd(cd, 2);
		free(cd);
		return (1);
	}
	pwd = get_pwd_now(getcwd(NULL, 0));
	replace_env(oldpwd);
	replace_env(pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}
