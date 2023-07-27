/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:59:55 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/28 02:43:53 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cx_bltin_parent(char **strarr)
{
	if (ft_strncmp(strarr[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(strarr[0], "export", 7) == 0 && strarr[1] != NULL)
		return (1);
	else if (ft_strncmp(strarr[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(strarr[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	cx_isbltin(char *str)
{
	if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	return (0);
}

void	to_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	ft_free_p2p_char(cmd);
	exit(errno);
}
