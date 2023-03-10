/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:17:18 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/10 16:14:36 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*strcmd;
	char	*pathnow;

	pathnow = (char *)malloc(PATH_MAX);
	//pathnow[PATH_MAX - 1] = '\0';
	while (1)
	{
		pathnow = getcwd(pathnow, PATH_MAX - 1);
		ft_strlcat(pathnow, " >> ", PATH_MAX);
		strcmd = readline("Minishell >> ");
		if (strcmd[0] != '\0')
			;
		else if (ft_strncmp(strcmd, "exit", 4) == 0)
			break ;
		// if empty string conti loop
	}
	return (0);
}
