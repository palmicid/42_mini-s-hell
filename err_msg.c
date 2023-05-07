/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 07:43:42 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/07 19:50:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_multipipe(void)
{
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("Minishell: syntax error near unexpected token `|'", 2);
}

void	err_q_nopair(void)
{
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("Minishell: no pair for single or double quote", 2);
}

void	err_redir(void)
{
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("Minishel: syntax error near unexpected token '<' '>'", 2);
}
