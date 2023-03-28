/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:12:53 by pruangde          #+#    #+#             */
/*   Updated: 2023/03/25 11:44:18 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int stst --> 2 = doubleQ " " , 1 = single ' ', 0 non
// use before split with pipe
typedef struct	s_strcut
{
	char			*str;
	int				stat;
	struct s_strcut	*next;
}					t_strcut;
