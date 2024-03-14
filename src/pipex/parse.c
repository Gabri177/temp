/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:38:49 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 06:39:31 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_command(t_pipex *pipex, int i)
{
	char	*command;
	char	*temp;
	int		j;

	if (pipex->cmds[i].args[0]
		&& is_command(pipex, ft_strdup(pipex->cmds[i].args[0]), i))
		return ;
	j = 0;
	if (!pipex->paths)
		return (cmd_not_found(pipex, i));
	while (pipex->paths[j])
	{
		temp = ft_strjoin(pipex->paths[j],
				"/");
		command = ft_strjoin(temp, pipex->cmds[i].args[0]);
		free(temp);
		if (is_command(pipex, command, i))
			break ;
		j++;
		if (!pipex->paths[j])
			cmd_not_found(pipex, i);
	}
}

void	find_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->envp)
		return ;
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4) != 0)
		i++;
	if (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4) == 0)
		pipex->paths = ft_split(pipex->envp[i] + 5, ":");
}

void static	open_outfile(t_pipex *pipex, t_mini *mini)
{
	if (mini->flag_append_output == TRUE)
		pipex->outfile = open(pipex->argv[pipex->size + 2],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipex->outfile = open(pipex->argv[pipex->size + 2],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void	open_files(t_pipex *pipex, t_mini *mini)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		if (access(pipex->argv[1], F_OK) != 0)
			error_message(pipex->argv[1]);
		else if (access(pipex->argv[1], R_OK) != 0)
			error_message(pipex->argv[1]);
		else
			ft_putstr_fd("Error: infile undefined\n", 2);
	}
	open_outfile(pipex, mini);
	if (pipex->outfile == -1)
	{
		if (access(pipex->argv[pipex->size + 2], W_OK) != 0)
			error_message(pipex->argv[pipex->size + 2]);
		else
			ft_putstr_fd("Error: outfile undefined\n", 2);
	}
}

bool	parse_input(t_pipex *pipex, t_mini *mini)
{
	int	i;

	find_paths(pipex);
	if (pipex->heredoc)
		open_here_doc(mini, pipex);
	else
		open_files(pipex, mini);
	i = 0;
	while (i < pipex->size)
	{
		pipex->cmds[i].found = false;
		pipex->cmds[i].args = \
			ft_split(pipex->argv[i + 2 + pipex->heredoc], " ");
		if (!pipex->cmds[i].args)
			return (false);
		if (!(i == 0 && pipex->infile == -1)
			&& !(i == pipex->size - 1 && pipex->outfile == -1))
			find_command(pipex, i);
		i++;
	}
	return (true);
}
