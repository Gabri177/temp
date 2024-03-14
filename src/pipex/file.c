/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 04:24:57 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 05:31:20 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	clean_outfile(t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open("./Libft/ft_printf/.outfile", O_WRONLY | O_TRUNC, 0777);
	close (fd);
	return (EXIT_SUCCESS);
}
