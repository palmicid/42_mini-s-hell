/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/18 21:18:56 by pruangde         ###   ########.fr       */
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
int			str_find_pair(char *str, int i, t_strcut **strlist);
int			strcut_nonq(char *str, int i, t_strcut **strlist);

// parser_3 - split cmd with pipe
t_lstcmd	*pipe_split(t_lstcmd *headcmd, t_strcut *lststr);
t_lstcmd	*sep_cmd(t_lstcmd *hdcmd);
t_strcut	*new_listcmd(t_lstcmd **nowcmd, t_strcut *leftstr);
t_lstcmd	*findpipe_malloc(t_strcut *lststr);
t_lstcmd	*listcmd_malloc(t_lstcmd *hdcmd, int np);

// parser_4 - split cmd with pipe cond.


// utils_1
t_strcut	*free_strcutlist(t_strcut *list);
t_lstcmd	*free_listcmd(t_lstcmd *lstcmd);
int			findpipe_count(char *str);
int			find_charpos(char *str, char c);
int			pipe_addstr_tolist(t_strcut *fwd, t_strcut *aft, t_strcut *src);

void		test_print(t_lstcmd *head);
void	test_printstrcut(t_strcut *fwd);

// utils_2
t_strcut	*splitp_error(t_strcut *leftcmd, t_strcut **tofree);

// err_msg
void		err_multipipe(void);

#endif


// cx if cmd can access before execute
// if cannot access or not found print cmd not found
// for multiple pipe or nothing between sep list and find if nothing
// bash: syntax error near unexpected token `|'
// 