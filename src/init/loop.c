/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:16 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 01:05:38 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*static void	check_file(t_mini *mini)
{
	int		fd;
	char	*str;

	fd = open(INFILE, O_RDONLY, O_TRUNC);
	str = get_next_line(fd);
	if (str)
		clean_outfile(mini);
	close (fd);
}*/

static void	reaload_set(t_mini **mini, char **line)
{
	char	*tem;

	tem = ft_strdup (*line);
	free (*line);
	(*mini)->arg_ori = split_filter ((*mini)->arg_ori, (*mini)->hash_env);
	*line = NULL;
	(*mini)->outfile = args_to_outfile (&(*mini)->arg_ori);
	(*mini)->infile = filter_args_infile (args_to_infile (&(*mini)->arg_ori));
	update_statu_write_outfile ((*mini), (*mini)->outfile);
	update_statu_write_dogii((*mini), (*mini)->infile);
	(*mini)->cmds_and_args = args_to_cmds_args ((*mini)->arg_ori);
	(*mini)->commands = args_to_cmds (&(*mini)->arg_ori);
	(*mini)->args = args_to_args ((*mini)->arg_ori);
	if ((*mini)->flag_here_doc != TRUE)
		add_history(tem);
	free (tem);
}

static void	apoy_line(char **line)
{
	if (*line)
	{
		free(*line);
		return ;
	}
	printf("\x1b[1;32mminishell\x1b[0m\x1b[1;36m > \x1b[0mexit");
	return ;
}

void	shell_loop(t_mini *mini)
{
	char	*line;

	while (1)
	{
		clean_outfile(mini);
		init_sig ();
		line = readline (PROMPT);
		if (line == NULL || ft_exit(line) == TRUE)
		{
			apoy_line (&line);
			break ;
		}
		if (!*line)
			continue ;
		g_sig_refresh (mini->hash_env, g_sig);
		mini->arg_ori = arg_abordar (line);
		if (!mini->arg_ori)
			continue ;
		reaload_set (&mini, &line);
		open_all_files(mini);
		ft_execute(mini);
		print (mini);
		init_re (mini);
	}
}
