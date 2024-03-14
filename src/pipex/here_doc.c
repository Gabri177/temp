/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:39:07 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 00:55:14 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc(t_pipex *pipex)
{
	char	*buf;

	while (1)
	{
		write(1, "minishell >", 11);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0')
			break ;
		if (ft_strlen(pipex->argv[2]) == ft_strlen(buf) - 1 && \
			ft_strncmp(pipex->argv[2], buf, ft_strlen(pipex->argv[2])) == 0)
			break ;
		write(pipex->infile, buf, ft_strlen(buf) - 1);
		write(pipex->infile, "\n", 1);
		free(buf);
	}
}

void	open_here_doc(t_pipex *pipex)
{
	pipex->infile = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC);
	if (pipex->infile == -1)
		error_message(NULL);
	here_doc(pipex);
	close(pipex->infile);
	pipex->infile = open(".here_doc", O_RDONLY);
	if (pipex->infile == -1)
	{
		unlink(".here_doc");
		error_message(NULL);
	}
	pipex->outfile = open(pipex->argv[pipex->size + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipex->outfile == -1)
	{
		if (access(pipex->argv[pipex->size + 2], W_OK) != 0)
			error_message(pipex->argv[pipex->size + 2]);
		else
			ft_putstr_fd("Error: outfile undefined\n", 2);
	}
}
