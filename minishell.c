/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsirikam <bsirikam@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/29 00:19:17 by bsirikam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// the child going to be parent for all program
void	process(char *strcmd)
{
	int		stat;
	t_cmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		cmdlist = str_split(strcmd);
		// to execute
		test_print(cmdlist);
		// to_exec();
		exit(errno);
	}
	else if (g_data->pid < 0)
		strerror(errno);
	else
	{
		waitpid(g_data->pid, &stat, WNOHANG);
	}
}

char	*sub_main(char *strcmd)
{
	strcmd = readline("Minishell >> ");
	if (!strcmd)
		return (NULL);
	else if (strcmd[0] == '\0')
		;
	else if (ft_strncmp(strcmd, "exit", 4) == 0)
	{
		free(strcmd);
		return (NULL);
	}
	else if (ft_strlen(strcmd) > 0)
		process(strcmd);
	return (strcmd);
}

// int	main(void)
// {
// 	char	*strcmd;

// 	strcmd = NULL;
// 	g_data = (t_data *)malloc(sizeof(t_data));
// 	if (!g_data)
// 		exit(EXIT_FAILURE);
// 	init_environ();
// 	signal_handling();
// 	while (1)
// 	{
// 		strcmd = sub_main(strcmd);
// 		if (!strcmd)
// 			break ;
// 		if (strcmd)
// 			free(strcmd);
// 	}
// 	if (!strcmd)
// 	{
// 		end_environ();
// 		ft_putendl_fd("exit", 1);
// 	}
// 	return (0);
// }

int main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmdtable;
	t_cmd	*cmdtable2;
	t_cmd	*cmdtable3;
	t_cmd	*cmdtable4;

	(void)argc;
	(void)argv;
	(void)envp;
	g_data = (t_data *)malloc(sizeof(t_data));
	if (!g_data)
		exit(EXIT_FAILURE);
	init_environ();
	cmdtable = malloc(sizeof(t_cmd));
	cmdtable->cmd = malloc(sizeof(char *) * 3);
	cmdtable2 = malloc(sizeof(t_cmd));
	cmdtable2->cmd = malloc(sizeof(char *) * 2);
	cmdtable3 = malloc(sizeof(t_cmd));
	cmdtable3->cmd = malloc(sizeof(char *) * 3);
	cmdtable4 = malloc(sizeof(t_cmd));
	cmdtable4->cmd = malloc(sizeof(char *) * 2);
	cmdtable->cmd[0] = ft_strdup("pwd");
	cmdtable->cmd[1] = NULL;
	cmdtable->cmd[2] = NULL;
	cmdtable->next = NULL;
	while (cmdtable)
	{
		execute(cmdtable);
		cmdtable = cmdtable->next;
	}
	return 0;
}
