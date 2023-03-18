/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/18 12:38:41 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <string.h>

typedef struct	s_data
{
	pid_t	pid;
	int		fortest;
}			t_data;

extern t_data	*g_data;


// minishell

// sig_handle
void	sig_int_handler(void);
void	signal_handling(void);

// utils_1


#endif
