/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:16:29 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 23:09:17 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_outfile(t_mini *mini, int out_fd, char *output_file)
{
	if (mini->flag_append_output)
		out_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(out_fd, STDOUT_FILENO);
	return (0);
}

int	single_redir(t_mini *mini, char *command, char *input_file,
	char *output_file)
{
	pid_t	pid;
	int		status;
	int		in_fd;
	int		out_fd;
	char	*args[2];

	out_fd = 0;
	pid = fork();
	if (pid == 0)
	{
		in_fd = open(input_file, O_RDONLY, 0777);
		if (in_fd == -1)
			return (printf ("minishll: %s: No such file or directory\n", input_file), 1);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		out_fd = open_outfile(mini, out_fd, output_file);
		close(out_fd);
		args[0] = command;
		args[1] = NULL;
		if (execvp(command, args) == -1)
			return (print_error("exceve failed on single_redir.c"));
	}
	else
	{
		waitpid(pid, &status, 0);
		g_sig = WIFEXITED (status);
	}
	return (0);
}
