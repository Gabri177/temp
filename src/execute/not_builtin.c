/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:24:12 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 09:26:43 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_args(char *command, char **arguments)
{
	int		i;
	int		size;
	char	*full;
	char	*temp;

	i = 0;
	size = 0;
	while (arguments[size])
		size++;
	full = ft_strdup(command);
	while (i < size)
	{
		temp = ft_strjoin(full, " ");
		free(full);
		full = temp;
		temp = ft_strjoin(full, arguments[i]);
		free(full);
		full = temp;
		i++;
	}
	return (full);
}

static int	num_args(char **arguments)
{
	int	i;

	i = 0;
	if (*arguments && ft_strcmp(arguments[0], "哈") == 0)
		return (0);
	while (arguments[i])
		i++;
	return (i);
}

static void	check_redirect(t_mini *mini, char *command)
{
	if (mini->flag_input == FALSE && (mini->flag_append_output == TRUE
			|| mini->flag_output == TRUE))
		single_redir(mini, command, INFILE,
			mini->outfile[arry_count(mini->outfile) - 1]);
	else if (mini->flag_input == TRUE && (mini->flag_append_output == FALSE
			&& mini->flag_output == FALSE))
		single_redir(mini, command, mini->infile[arry_count(mini->infile) - 1],
			OUTFILE);
	else if (mini->flag_input == TRUE && (mini->flag_append_output == TRUE
			|| mini->flag_output == TRUE))
		single_redir(mini, command, mini->infile[arry_count(mini->infile) - 1],
			(mini->outfile[arry_count(mini->outfile) - 1]));
}

void	not_builtin(char *command, char **arguments, t_mini *mini, int flag)
{
	char	*full;
	char	**envp;
	int		num_arg;

	envp = hash_to_arry(mini->hash_env);
	num_arg = num_args(arguments);
	if (num_arg >= 1)
	{
		full = join_args(command, arguments);
		ft_exec_single(full, envp);
	}
	if (mini->flag_input == TRUE || mini->flag_append_output == TRUE
		|| mini->flag_output == TRUE)
		check_redirect (mini, command);
	else
		ft_exec_single(command, envp);
	free(envp);
	(void)flag;
}
