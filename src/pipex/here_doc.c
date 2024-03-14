/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:39:07 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 06:59:49 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**change_argv(t_mini *mini)
{
	char	**new;
	int		i;
	int		j;

	i = 2;
	j = 0;
	new = ft_calloc((mini->argc + 4), sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup("./minishell");
	new[1] = ft_strdup("./Libft/ft_printf/.infile");
	while (mini->cmds_and_args[j])
	{
		new[i] = ft_strdup(mini->cmds_and_args[j]);
		j++;
		i++;
	}
	if (mini->flag_output == FALSE && mini->flag_append_output == FALSE)
		new[i] = ft_strdup("./Libft/ft_printf/.outfile");
	else
		new[i] = ft_strdup(mini->outfile[arry_count(mini->outfile) - 1]);
	return (new);
}

void	here_doc(t_pipex *pipex)
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
		if (ft_strlen(pipex->argv[2]) == ft_strlen(buf) - 1 && \
			ft_strncmp(pipex->argv[2], buf, ft_strlen(pipex->argv[2])) == 0)
			break ;
		write(fd, buf, ft_strlen(buf) - 1);
		write(fd, "\n", 1);
		free(buf);
	}
	close(fd);
}

void	open_here_doc(t_mini *mini, t_pipex *pipex)
{
	char	**new;

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
	pipex->outfile = open(pipex->argv[pipex->size + 4],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipex->outfile == -1)
	{
		if (access(pipex->argv[pipex->size + 2], W_OK) != 0)
			error_message(pipex->argv[pipex->size + 2]);
		else
			ft_putstr_fd("Error: outfile undefined\n", 2);
	}
	new = change_argv(mini);
	pipex_bonus(mini, mini->argc + 3, new, hash_to_arry(mini->hash_env));
}
