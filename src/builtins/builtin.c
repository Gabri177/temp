/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:20:52 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 07:45:39 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *command, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->is_builtin[i] != NULL)
	{
		if (ft_strcmp (command, mini->is_builtin[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	exec_builtin(char *command, char **arguments, t_mini *mini)
{
	if (ft_strcmp(arguments[0], "哈") == 0 || ft_strcmp(arguments[0], "\b") == 0)
	{
		free (arguments[0]);
		arguments[0] = ft_strdup (" ");
	}
	if (ft_strcmp("echo", ft_lower(command)) == 0)
		ft_echo(mini, arguments, FALSE);
	else if (ft_strcmp("echo -n", ft_lower(command)) == 0)
		ft_echo(mini, arguments, TRUE);
	else if (ft_strcmp("cd", ft_lower(command)) == 0)
		ft_cd(mini, arguments[0]);
	else if (ft_strcmp("pwd", ft_lower(command)) == 0)
		ft_pwd(mini);
	else if (ft_strcmp("export", ft_lower(command)) == 0)
		ft_export(mini, mini->args[0][0]);
	else if (ft_strcmp("unset", ft_lower(command)) == 0)
		ft_unset(mini, mini->args[0][0]);
	else if (ft_strcmp("env", ft_lower(command)) == 0)
		ft_env(mini);
}
