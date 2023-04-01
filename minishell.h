/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/31 00:22:59 by pruangde         ###   ########.fr       */
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

// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct	s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;


// minishell

// sig_handle
void		sig_int_handler(int sig);
void		signal_handling(void);

// parser_1
t_cmd		*str_split(char *str, t_cmd *table);

// parser_2
int			str_find_pair(char *str, int i, t_strcut **strlist);
int			strcut_nonq(char *str, int i, t_strcut **strlist);

// utils_1
t_strcut	*free_strcutlist(t_strcut *list);

#endif
