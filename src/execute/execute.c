/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:58:56 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 00:51:30 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_execute(t_mini *mini)
{
	int		i;
	int		pipe_found;
	char	**argv;

	i = 0;
	pipe_found = 0;
	if (!mini->commands)
		return (EXIT_SUCCESS);
	while (mini->commands[i])
	{
		if (mini->commands[i][0] == '|')
		{
			mini->argc = arry_count (mini->cmds_and_args);
			argv = check_cmds_and_args(mini);
			pipex_bonus(mini, mini->argc + 3,
				argv, hash_to_arry(mini->hash_env));
			arry_display (argv);
			arry_destory (argv);
			pipe_found = 1;
		}
		i++;
	}
	if (!pipe_found)
		single_command(mini);
	return (EXIT_SUCCESS);
}
