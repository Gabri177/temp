/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:18:34 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 01:09:08 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//!!!!!!!
#include "../../include/minishell.h"

int	test = 0;

char	**parse_single_here_doc(t_mini *mini)
{
	char	**here_doc;

	here_doc = malloc((4) * sizeof(char *));
	if (here_doc == NULL)
		return (NULL);
	here_doc[0] = ft_strdup("./minishell");
	here_doc[1] = ft_strdup(mini->infile[arry_count(mini->infile) - 1]);
	here_doc[2] = ft_strdup(mini->commands[0]);
	here_doc[3] = NULL;
	return (here_doc);
}

void	here_doc_producer(char *delimiter)
{
	char	*buf;
	char	*tem;

	while (1)
	{
		write (1, "minishell >", 11);
		if (delimiter)
			tem = ft_strjoin (delimiter, "\n");
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0' || test == 1)
		{
			test = 0;
			break ;
		}
		if (buf && is_strsame (tem, buf))
			break ;
		if (buf)
			free (buf);
		if (tem)
			free (tem);
	}
}

void	sig_hand(int sig)
{
	(void)sig;
	test = 1;
	printf ("\n");
}

void	here_doc_consumer(char *cmd, char *arg1)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = 0;
	pipe (fd);
	pid = fork();
	if (!pid)
	{
		signal (SIGINT, sig_hand);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		here_doc_producer(arg1);
		close(fd[1]);
		execvp(cmd, (char *[]){cmd, NULL});
		exit(1);
	}
	else
	{
		close(fd[1]);
		while ((read(fd[0], buffer, sizeof(buffer))) > 0)
			write(STDOUT_FILENO, buffer, bytes_read);
		close(fd[0]);
		wait(NULL);
	}
}

int	single_here_doc(int argc, char **argv)
{
	char	*cmd;

	if (argc != 3)
	{
		printf("Usage: ./minishell 'delimiter' 'command'\n");
		exit(1);
	}
	cmd = argv[2];
	here_doc_consumer(cmd, argv[1]);
	return (0);
}
