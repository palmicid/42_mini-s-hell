/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/07 20:46:06 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "./libft/libft.h"
# include "./libft/libft.h"
# include <limits.h>
# include <sys/signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_data
{
	pid_t	pid;
	char	**env;
	int		fortest;
}			t_data;

extern t_data	*g_data;

typedef struct	s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct	s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;

typedef struct	s_listcmd
{
	int					cmd_no;
	struct s_strcut		*strcut;
	struct s_listcmd	*next;
}						t_lstcmd;


// minishell

// sig_handle
void		sig_int_handler(int sig);
void		signal_handling(void);

// parser_1 - main split
t_cmd		*str_split(char *str, t_cmd *table);

// parser_2 - quote split and add stat q or nonq
t_strcut	*qsp_split(char *str);


// parser_3 - split meta char
t_strcut	*meta_split(t_strcut *list);


// parser_4 -


// utils_1
t_strcut	*free_strcutlist(t_strcut **list);
t_lstcmd	*free_listcmd(t_lstcmd *lstcmd);
int			find_charpos(char *str, char c);
t_strcut	*lastlist_strcut(t_strcut *list);
int			cont_char(char *str, int i, char c);

// ------ TEST
void		test_print(t_lstcmd *head);
void	test_printstrcut(t_strcut *fwd);

// utils_2
int			find_pair(char *str, int i);
int			count_liststrcut(t_strcut *list);


// err_msg
void		err_multipipe(void);
void		err_q_nopair(void);

#endif


// cx if cmd can access before execute
// if cannot access or not found print cmd not found
// for multiple pipe or nothing between sep list and find if nothing
// bash: syntax error near unexpected token `|'
//