/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 07:43:42 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/29 02:48:42 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_redirpipe(char *str)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token", 2);
	ft_putstr_fd(" '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

void	err_q_nopair(void)
{
	ft_putendl_fd("Minishell: no pair for single or double quote", 2);
}

void	err_redir(void)
{
	ft_putendl_fd("Minishel: syntax error near unexpected token '<' '>'", 2);
}

void	err_msgexec(char *str, char *msg)
{
	if (str && msg)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
	else if (msg)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
}
