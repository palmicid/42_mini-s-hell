/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:52:46 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/30 22:45:44 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
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

// ctrl+C and ctrl+backspace
void	signal_handling(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sig_int.sa_handler = sig_int_handler;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
