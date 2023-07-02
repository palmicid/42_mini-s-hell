/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:18:15 by pruangde          #+#    #+#             */
/*   Updated: 2023/07/02 13:16:13 by pruangde         ###   ########.fr       */
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
	char				*strcmd;
}						t_data;

// extern char		**environ;
extern t_data	*g_data;

typedef struct s_pipe
{
	int	*fd;
	int	pipe_count;
	int	size_fd;
}				t_pipe;

typedef struct s_cmdlist
{
	struct s_strcut		*cmd;
	struct s_cmdlist	*next;
}					t_cmdlist;

typedef struct s_cmd
{
	char	**cmd;
	int		fdin;
	int		fdout;
}			t_cmd;

typedef struct s_c
{
	int	st;
	int	i;
	int	j;
}		t_c;

typedef struct s_heredoc
{
	int		has_hd;
	int		fdhd[2];
	// char	*str;
}			t_heredoc;

// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;

// minishell
void		process(void);

// sig_handle
void		sig_int_handler(int sig);
void		signal_handling();

// env
int			init_environ(char **env);
int			end_environ(void);
char		*my_getenv(char *str);

// parser_1 - main split + split long list to cmd
t_cmdlist		*str_split(char *str, t_data *data);

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
// void		test_print(t_cmdlist *head);
void		test_printcmdlist(t_cmdlist *head);
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
t_cmdlist		*free_cmdlist(t_cmdlist **lstcmd);

// utils_5
t_strcut	*inside_cxmetavalid(t_strcut **head, char *str);
t_strcut	*createnew_strcut(void);
t_cmdlist	*createnew_lstcmd(void);
t_c			*create_countptr(void);
int			which_redir(char *str);

// utils_6	open file and heredoc
char		**get_cmd(t_strcut *head);
void		rec_heredoc(char *eof, t_heredoc *hd);
int			to_heredoc(t_strcut *list, t_heredoc *hd);
int			openfile(char *str, int *fd, int mode);
int			fd_redir(t_strcut *cmd, int *fdin, int *fdout);


// err_msg
void		err_redirpipe(char *str);
void		err_q_nopair(void);
void		err_redir(void);
void		err_msgexec(char *str, char *msg);
void		err_heredoc_eof(char *str);

// execute_1
void		to_execute(t_cmdlist *cmd);

// execute_2
int			cx_bltin_parent(char **strarr);
int			cx_isbltin(char *str);

// not mine
// int			execute_2(t_cmdlist *cmdtable, char *pnamewp);
// int			check_builtin_fork(t_cmdlist *cmdtable);
// void		execute(t_cmdlist *cmdtable);
// void		execve_part(t_cmdlist *cmdtable, char **path, char *tmp_env);

// built_in
int			get_env_size(void);
int			is_home_with_path(t_cmdlist *cmdtable);
int			home_with_path(t_cmdlist *cmdtable, char *oldpwd);
int			validate_env(char *env);
int			normal_path(t_cmdlist *cmdtable, char *oldpwd);
char		*remove_quote(char *cmd);
char		*get_key(char *s);
char		*getvalue(char *s, char c);
char		*remove_quote(char *cmd);
char		*get_pwd_now(char *pwd);
char		*my_get_env(void);
char		*addslash(char *cmd);
char		*hash_name(char *filename);
void		ft_env(t_cmdlist *cmdtable);
void		ft_export(t_cmdlist *cmdtable);
void		ft_export_noarg(void);
void		ft_export_witharg(t_cmdlist *cmdtable);
void		replace_env(char *env);
void		ft_pwd(t_cmdlist *cmdtable);
void		ft_echo(t_cmdlist *cmdtable);
void		ft_unset(t_cmdlist *cmdtable);
void		ft_cd(t_cmdlist *cmdtable);
void		ft_exit(t_cmdlist *cmdtable);

#endif

// fixing signal and if var ?