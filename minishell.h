/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/06 21:59:41 by bsirikam         ###   ########.fr       */
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

typedef struct s_data
{
	pid_t				pid;
	char				**env;
	int					exit_stat;
}						t_data;

extern char		**environ;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_c
{
	int	st;
	int	i;
	int	j;
}		t_c;


// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;

// minishell
void		process(char *strcmd, t_data *data);

// sig_handle
void		sig_int_handler(int sig);
void		signal_handling();

// env
int			init_environ(t_data *data);
int			end_environ(t_data *data);

// parser_1 - main split + split long list to cmd
t_cmd		*str_split(char *str, t_data *data);

// parser_2 - quote split and add stat q or nonq
t_strcut	*qsp_split(char *str);

// parser_3 - split meta char | < << >> >
t_strcut	*meta_split(t_strcut *head);

// parser_4 - remove quote
t_strcut	*remove_q_xpand(t_strcut *head, t_data *data);

// parser_5 - expand
void		expand_var(t_strcut *tmp, t_data *data);

// parser_6 - join str from list
void		lst_strjoin(t_strcut *current, t_strcut **tmp);

// utils_1
t_strcut	*free_strcutlist(t_strcut **list);
t_strcut	*free_strcut(t_strcut *tofree);
int			find_charpos(char *str, char c);
t_strcut	*lastlist_strcut(t_strcut *list);
int			cont_char(char *str, int i, char c);

// ------ TEST
int			to_execute(t_cmd *cmds);
void		test_print(t_cmd *head);
void		test_printstrcut(t_strcut *fwd);
void		test_printonestrcut(t_strcut *cur);

// utils_2
int			find_pair(char *str, int i);
int			count_liststrcut(t_strcut *list);
int			ft_isspace(int c);
int			count_samechar(char *str, int pos);
int			find_metapos(char *str);

// utils_3
int			add_metastat(char *str);
t_strcut	*search_liststrcut(t_strcut *head, t_strcut *now);
t_strcut	*new_nowsepmeta(t_strcut *tmphd);
t_strcut	*cx_meta_valid(t_strcut *head);
void		restat_normal(t_strcut *head);

// utils_4
int			find_q_doll(char *str);
void		set_error(t_strcut *cur);
void		remove_q(t_strcut *head);
int			next_i_qsplit(char *str, int i);
t_cmd		*free_cmdlist(t_cmd *lstcmd);

// utils_5
t_strcut	*inside_cxmetavalid(t_strcut **head, char *str);
t_strcut	*createnew_strcut(void);
t_cmd		*createnew_lstcmd(void);
t_c			*create_countptr(void);
// err_msg
void		err_redirpipe(char *str);
void		err_q_nopair(void);
void		err_redir(void);

// execute
void		execute(t_cmd *cmdtable);

// built_in
int			get_env_size(void);
int			validate_env(char *env);
char		*remove_quote(char *cmd);
char		*get_key(char *s);
char		*getvalue(char *s, char c);
void		ft_env(t_cmd *cmdtable);
void		ft_export(t_cmd *cmdtable);
void		ft_export_noarg(void);
void		ft_export_witharg(t_cmd *cmdtable);
void		replace_env(char *env);
void		ft_pwd(t_cmd *cmdtable);
void		ft_echo(t_cmd *cmdtable);
void		ft_unset(t_cmd *cmdtable);

#endif

// fixing signal and if var ?