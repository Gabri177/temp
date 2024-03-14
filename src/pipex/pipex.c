/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:38:38 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 04:42:07 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_command(t_pipex *pipex, char *command, int i)
{
	if (!command)
		return (false);
	if (access(command, F_OK) == 0 && ft_strncmp(command, "/", 1) == 0)
	{
		pipex->cmds[i].path = ft_strdup(command);
		if (!pipex->cmds[i].path)
			return (false);
		free(command);
		pipex->cmds[i].found = true;
		return (true);
	}
	free(command);
	return (false);
}

bool	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc((pipex->size) * sizeof(int *));
	if (!pipex->pipes)
		return (false);
	while (i < pipex->size)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			return (false);
		if (pipe(pipex->pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

bool	wait_pids(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->size && pipex->child_pids[i] > 0)
	{
		waitpid(pipex->child_pids[i], &status, 0);
		g_sig = WIFEXITED (status);
		i++;
	}
	if (pipex->outfile == -1)
		pipex->exitcode = 1;
	else if (!pipex->cmds[i - 1].found)
		pipex->exitcode = 127;
	else
		pipex->exitcode = 0;
	return (true);
}

bool	allocate_pids(t_pipex *pipex)
{
	int	i;

	pipex->child_pids = malloc(pipex->size * sizeof(int));
	if (!pipex->child_pids)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->child_pids[i] = -1;
		i++;
	}
	return (true);
}

bool	execute(t_pipex *pipex)
{
	int	pid;
	int	i;

	if (!allocate_pids(pipex))
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pid = fork();
		if (pid == 0)
		{
			init_sig_child ();
			children(*pipex, i);
		}
		else if (pid > 0)
			pipex->child_pids[i] = pid;
		else
			return (close_all_fds(pipex), false);
		i++;
	}
	close_all_fds(pipex);
	wait_pids(pipex);
	return (true);
}
