
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:32:29 by pruangde          #+#    #+#             */
/*   Updated: 2023/04/12 12:30:53 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stat	0 == non q
// 		1 == single
//		2 == double
//		3 == pipe

// continue sep space and pipe 
// if == space --> sep list token
// if == pipe  --> sep and create new for only pipe