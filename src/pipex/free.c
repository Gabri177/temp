/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:39:13 by javgao            #+#    #+#             */
/*   Updated: 2024/03/12 11:28:34 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	close_all_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->pipes)
		return (false);
	while (i < pipex->size && pipex->pipes[i])
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	return (true);
}

bool	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size && pipex->cmds && pipex->cmds[i].args)
	{
		ft_free_arr(pipex->cmds[i].args);
		if (pipex->cmds[i].found)
			free(pipex->cmds[i].path);
		i++;
	}
	free(pipex->cmds);
	if (pipex->paths)
		ft_free_arr(pipex->paths);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->child_pids)
		free(pipex->child_pids);
	if (pipex->heredoc)
		unlink(".here_doc");
	return (true);
}
