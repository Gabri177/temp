/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:44:49 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 10:36:46 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(char *error)
{
	printf("%s\n", error);
	g_sig = 1;
	return (EXIT_FAILURE);
}
