/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:34:33 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 09:27:23 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_mini(t_mini *mini, char **envp)
{
	mini->line = NULL;
	mini->arg_ori = NULL;
	mini->paths = NULL;
	mini->infile = NULL;
	mini->outfile = NULL;
	mini->commands = NULL;
	mini->args = NULL;
	mini->cmds_and_args = NULL;
	mini->argc = 0;
	mini->flag_append_output = FALSE;
	mini->flag_output = FALSE;
	mini->flag_unset_path = FALSE;
	mini->flag_here_doc = FALSE;
	mini->flag_input = FALSE;
	init_builtin(mini);
	init_env(mini, envp);
}

void	init_builtin(t_mini *mini)
{
	mini->is_builtin[0] = "echo";
	mini->is_builtin[1] = "echo -n";
	mini->is_builtin[2] = "cd";
	mini->is_builtin[3] = "pwd";
	mini->is_builtin[4] = "export";
	mini->is_builtin[5] = "unset";
	mini->is_builtin[6] = "env";
	mini->is_builtin[7] = NULL;
}

void	init_env(t_mini *mini, char **envp)
{
	int		i;
	int		len_to_equal;
	char	*key;

	i = 0;
	len_to_equal = 0;
	mini->hash_env = hash_init();
	g_sig = 0;
	hash_push (mini->hash_env, "?", "?=0");
	while (envp[i])
	{
		len_to_equal = ft_strchrlen(envp[i], '=');
		key = ft_substr(envp[i], 0, len_to_equal);
		hash_push(mini->hash_env, key, envp[i]);
		free (key);
		i++;
	}
}

void	init_re(t_mini *mini)
{
	int		fd;
	char	*str;

	arry_destory (mini->arg_ori);
	mini->arg_ori = NULL;
	arry_destory (mini->outfile);
	mini->outfile = NULL;
	arry_destory (mini->infile);
	mini->infile = NULL;
	arry_destory (mini->cmds_and_args);
	mini->cmds_and_args = NULL;
	arry_destory (mini->commands);
	mini->commands = NULL;
	argss_destory (mini->args);
	mini->args = NULL;
	mini->flag_append_output = FALSE;
	mini->flag_output = FALSE;
	mini->flag_here_doc = FALSE;
	mini->flag_input = FALSE;
	fd = open(INFILE, O_RDONLY);
	str = get_next_line(fd);
	if (str)
		clean_outfile(mini);
	close (fd);
}
