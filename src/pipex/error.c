/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:39:19 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 06:49:54 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_message(char *file)
{
	if (file)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	cmd_not_found(t_pipex *pipex, int i)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(pipex->cmds[i].args[0], 2);
	ft_putstr_fd("\n", 2);
	pipex->cmds[i].found = false;
}
