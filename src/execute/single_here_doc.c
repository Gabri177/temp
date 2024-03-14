/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:18:34 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 10:01:31 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_here_doc(t_mini *mini)
{
	char	*buf;
	int		fd;

	fd = open(INFILE, O_WRONLY, 0777);
	while (1)
	{
		write(1, "minishell >", 11);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0')
			break ;
		if (ft_strncmp(mini->infile[arry_count(mini->infile) - 1], buf,
		ft_strlen(mini->infile[arry_count(mini->infile) - 1])) == 0)
			break ;
		write(fd, buf, ft_strlen(buf) - 1);
		write(fd, "\n", 1);
		free(buf);
	}
	close(fd);
}

void	open_single_here_doc(t_mini *mini)
{
	mini->here_doc_file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC);
	if (mini->here_doc_file == -1)
		print_error("open failed");
	single_here_doc(mini);
	close(mini->here_doc_file);
	mini->here_doc_file = open(".here_doc", O_RDONLY);
	if (mini->here_doc_file == -1)
	{
		unlink(".here_doc");
		error_message(NULL);
	}
	if (mini->flag_append_output == TRUE || mini->flag_output == TRUE)
		mini->here_outfile = open(mini->outfile[arry_count(mini->outfile) - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		mini->here_outfile = open(OUTFILE, O_WRONLY, O_TRUNC);
	if (mini->here_outfile == -1)
		print_error("open failed on single here_doc");
	mini->flag_here_doc = FALSE;
	if (mini->flag_append_output == TRUE || mini->flag_output == TRUE)
		single_redir(mini, mini->commands[0], INFILE,
		mini->outfile[arry_count(mini->outfile) - 1]);
	else
		single_redir(mini, mini->commands[0], INFILE, OUTFILE);
}
