/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:48:21 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/27 02:57:50 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strcut	*free_strcutlist(t_strcut **list)
{
	t_strcut	*head;
	t_strcut	*now;

	head = list[0];
	while (head)
	{	
		now = head;
		head = head->next;
		if (now->str)
			free(now->str);
		free(now);
	}
	now = NULL;
	list[0] = NULL;
	return (list[0]);
}

t_strcut	*free_strcut(t_strcut *tofree)
{
	if (tofree->str)
		free(tofree->str);
	free(tofree);
	tofree = NULL;
	return (tofree);
}

int	find_charpos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_strcut	*lastlist_strcut(t_strcut *list)
{
	t_strcut	*ret;

	ret = list;
	if (ret)
	{
		while (ret->next)
		{
			ret = ret->next;
		}
	}
	return (ret);
}

// skip same char return next pos to last c
int	cont_char(char *str, int i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

// 	-----------TEST-------------
void	test_print(t_cmd *head)
{
	t_cmd	*ptr = head;
	int		in = 0;

	while (ptr)
	{
		in = 0;
		printf("CMD == ");
		while (ptr->cmd[in])
		{
			printf("|%s", ptr->cmd[in]);
			in++;
		}
		printf("|\n");
		ptr = ptr->next;
	}
}

void	test_printstrcut(t_strcut *fwd)
{
	t_strcut	*ptr;
	ptr = fwd;
	ft_putstr_fd("\n=======STRCUT_PRINT==========\n", 2);
	while (ptr)
	{
		if (ptr->str)
			ft_putstr_fd("stat = ", 2);
			ft_putnbr_fd(ptr->stat, 2);
			ft_putstr_fd(" | str = [", 2);
			ft_putstr_fd(ptr->str, 2);
			ft_putstr_fd("]\n", 2);
			
			// printf("[%s] - ", ptr->str);
			
			ptr = ptr->next;
	}
	ft_putstr_fd("\n=============================\n", 2);
}

void	test_printonestrcut(t_strcut *cur)
{
	if (cur)
	{
		ft_putstr_fd("stat = ", 2);
		ft_putnbr_fd(cur->stat, 2);
		ft_putstr_fd(" | str = [", 2);
		ft_putstr_fd(cur->str, 2);
		ft_putstr_fd("]\n", 2);
	}
}

// 	-----------TEST-------------