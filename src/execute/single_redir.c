/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:16:29 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 10:50:30 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_input_redirection(char *input_file)
{
	int	in_fd;

	in_fd = open(input_file, O_RDONLY);
	if (in_fd == -1)
		return (print_error("open failed on infile redirection"));
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	return (0);
}

int	execute_command(t_mini *mini, char *command)
{
	(void)command;
	ft_exec_single(mini->cmds_and_args[0], hash_to_arry(mini->hash_env));
	exit(EXIT_FAILURE);
}

int	setup_output_redirection(char *output_file)
{
	int	out_fd;

	out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd == -1)
		return (print_error("open failed on outfile redirection"));
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	return (0);
}

int	handle_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_sig = WIFEXITED (status);
	return (0);
}

int	single_redir(t_mini *mini, char *command, char *infile, char *outfile)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (print_error("fork"));
	else if (pid == 0)
	{
		setup_input_redirection(infile);
		setup_output_redirection(outfile);
		execute_command(mini, command);
	}
	else
	{
		handle_parent_process(pid);
		waitpid(pid, &status, 0);
	}
	return (0);
}
