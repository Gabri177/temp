/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:39:26 by javgao            #+#    #+#             */
/*   Updated: 2024/03/12 19:06:26 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect(t_pipex pipex, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(output);
}

void	children(t_pipex pipex, int i)
{
	if (!pipex.cmds[i].found)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	if (i == 0)
		child(pipex, i, pipex.infile, pipex.pipes[i][1]);
	else if (i != pipex.size - 1)
		child(pipex, i, pipex.pipes[i - 1][0], pipex.pipes[i][1]);
	else
		child(pipex, i, pipex.pipes[i - 1][0], pipex.outfile);
}

void	child(t_pipex pipex, int i, int input, int output)
{
	redirect(pipex, input, output);
	close_all_fds(&pipex);
	if (execve(pipex.cmds[i].path, pipex.cmds[i].args, pipex.envp) == -1)
	{
		free_pipex(&pipex);
		error_message(NULL);
	}
	exit(1);
}
