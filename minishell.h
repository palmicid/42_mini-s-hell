/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/24 11:13:51 by pruangde         ###   ########.fr       */
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
	char	**env;
	int		fortest;
}			t_data;

extern t_data	*g_data;

typedef struct	s_cmd
{
	char	*filein;
	char	*fileout;
	char	***allcmd;
}			t_cmd;


// minishell

// sig_handle
// void	sig_int_handler(int sig);
// void	signal_handling(void);

// 

// utils_1


#endif
