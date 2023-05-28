/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:50:38 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/26 20:44:41 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_q_doll(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

// set stat = -1
void	set_error(t_strcut *cur)
{
	cur->stat = -1;
	return ;
}

void	remove_q(t_strcut *head)
{
	t_strcut	*tmp;

	tmp = head;
	while (tmp)
	{
		if (find_charpos(tmp->str, 34) >= 0)
		{
			tmp->stat = 2;
			tmp->str = ft_strtrim(tmp->str, "\"");
		}
		else if (find_charpos(tmp->str, 39) >= 0)
		{
			tmp->stat = 1;
			tmp->str = ft_strtrim(tmp->str, "'");
		}
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		if (tmp->str == NULL)
			set_error(tmp);
		tmp = tmp->next;
	}
}

int	next_i_qsplit(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (i - 1);
		i++;
	}
	return (i - 1);
}

t_cmd	*free_cmdlist(t_cmd *lstcmd)
{
	t_cmd	*tofree;

	tofree = lstcmd;
	while (lstcmd)
	{
		lstcmd = lstcmd->next;
		if (tofree->cmd)
			ft_free_p2p_char(tofree->cmd);
		free(tofree);
		tofree = lstcmd;
	}
	return (lstcmd);
}
