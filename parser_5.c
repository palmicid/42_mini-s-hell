/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 04:15:44 by pruangde          #+#    #+#             */
/*   Updated: 2023/05/27 17:31:38 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if i++ == nothing malloc 
static char	*getvarname(char *str, int *i)
{
	char	*name;
	int		st;

	(*i)++;
	if (ft_isalnum(str[*i]) == 0)
		name = ft_calloc(1, sizeof(char));
	else
	{
		st = *i;
		while (str[*i] && (ft_isalnum(str[*i]) == 1))
			(*i)++;
		name = ft_strndup(str + st, (*i - st));
	}
	return (name);
}

static char	*sub_expand_proc(char *str, int *i, char *fin)
{
	char	*name;
	char	*var;

	name = getvarname(str, i);
	if (!name)
		return (NULL);
	var = getenv(name);
	if (!var)
		return (ft_freemanycharptr(name, 0, 0, 0));
	fin = ssp_strjoin(fin, var, 1, 0);
	free(name);
	return (fin);
}

static char	*subinsub_expand(char *fin, int *st, int *i, t_strcut *cur)
{
	if (*st != *i)
		fin = ssp_strnjoin(fin, cur->str + *st, (*i - *st), 0);
	if (!fin)
		return (fin);
	fin = sub_expand_proc(cur->str, i, fin);
	if (!fin)
		return (fin);
	*st = (*i)--;
	return (fin);
}

// pass 0 to both int 
void	sub_expand(t_strcut *cur)
{
	char	*fin;
	int		st;
	int		i;

	st = 0;
	i = 0;
	fin = ft_calloc(1, sizeof(char));
	if (!fin)
		return (set_error(cur));
	while (cur->str[i])
	{
		if (cur->str[i] == '$')
		{
			fin = subinsub_expand(fin, &st, &i, cur);
			if (!fin)
				return (set_error(cur));
		}
		i++;
	}
	if (st != i)
		fin = ssp_strjoin(fin, cur->str + st, 1, 0);
	free(cur->str);
	cur->str = fin;
}

void	expand_var(t_strcut *head)
{
	t_strcut	*cur;

	cur = head;
	while (cur)
	{
		if (cur->stat == 0 || cur->stat == 2)
		{
			sub_expand(cur);
			if (cur->stat == -1)
				return (set_error(head));
		}
		cur = cur->next;
	}
}
