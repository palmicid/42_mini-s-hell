/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:52:46 by pruangde          #+#    #+#             */
/*   Updated: 2023/08/01 23:25:06 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler_normal(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_int_handler_exec(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

// ctrl+C and ctrl+backspace
void	signal_handling(int mode)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	if (mode == 1)
		sig_int.sa_handler = sig_int_handler_normal;
	else if (mode == 2)
		sig_int.sa_handler = sig_int_handler_exec;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
