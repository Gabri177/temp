/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:38:55 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 09:42:30 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipex_bonus(t_mini *mini, int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 2)
		return (ft_putstr_fd("Error: Not enough arguments\n", 2), EXIT_FAILURE);
	if (!pipex_init(&pipex, argc, argv, envp))
		return (free_pipex(&pipex), error_message(NULL), EXIT_FAILURE);
	if (argc < 2 + pipex.heredoc)
		return (ft_putstr_fd("Error: Not enough arguments\n", 2)
			, free_pipex(&pipex), EXIT_FAILURE);
	if (!parse_input(&pipex, mini))
		return (free_pipex(&pipex), EXIT_FAILURE);
	if (!create_pipes(&pipex))
		return (free_pipex(&pipex), error_message(NULL), EXIT_FAILURE);
	if (!execute(&pipex))
		return (free_pipex(&pipex), error_message(NULL), pipex.exitcode);
	free_pipex(&pipex);
	return (pipex.exitcode);
}

bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmds = NULL;
	pipex->pipes = NULL;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->child_pids = NULL;
	pipex->exitcode = EXIT_SUCCESS;
	pipex->heredoc = false;
	if (ft_strncmp(pipex->argv[1], "here_doc", 9) == 0
		&& ft_strncmp(pipex->argv[0], "./minishell", 11) == 0)
		pipex->heredoc = true;
	pipex->size = argc - 3 - pipex->heredoc;
	if (!init_cmds(pipex))
		return (false);
	return (true);
}

bool	init_cmds(t_pipex *pipex)
{
	int	i;

	pipex->cmds = malloc(pipex->size * sizeof(t_cmd));
	if (!pipex->cmds)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->cmds[i].args = NULL;
		pipex->cmds[i].found = false;
		pipex->cmds[i].path = NULL;
		i++;
	}
	return (true);
}
