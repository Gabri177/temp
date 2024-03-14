/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds_and_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:40:35 by javgao            #+#    #+#             */
/*   Updated: 2024/03/14 01:08:08 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**set_mem(t_mini *mini)
{
	char	**new;

	if (mini->flag_here_doc == TRUE)
		new = ft_calloc ((mini->argc + 5), sizeof(char *));
	else
		new = ft_calloc ((mini->argc + 4), sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup("./minishell");
	if (mini->infile == NULL)
		new[1] = ft_strdup("./Libft/ft_printf/.infile");
	else if (mini->flag_here_doc == TRUE)
	{
		new[1] = ft_strdup("here_doc");
		new[2] = ft_strdup(mini->infile[arry_count(mini->infile) - 1]);
	}
	else
		new[1] = ft_strdup(mini->infile[arry_count(mini->infile) - 1]);
	return (new);
}

char	**check_cmds_and_args(t_mini *mini)
{
	char	**new;
	int		i;
	int		j;

	j = 0;
	new = set_mem (mini);
	if (!new)
		return (NULL);
	if (mini->flag_here_doc == TRUE)
		i = 3;
	else
		i = 2;
	while (mini->cmds_and_args[j])
	{
		new[i] = ft_strdup (mini->cmds_and_args[j]);
		j ++;
		i ++;
	}
	if (mini->flag_output == FALSE && mini->flag_append_output == FALSE)
		new[i] = ft_strdup("./Libft/ft_printf/.outfile");
	else
		new[i] = ft_strdup(mini->outfile[arry_count(mini->outfile) - 1]);
	return (new);
}
