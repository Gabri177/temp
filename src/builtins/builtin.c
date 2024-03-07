/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:20:52 by javgao            #+#    #+#             */
/*   Updated: 2024/03/06 10:46:14 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Function to check if the command written is builtin. 
	The idea is to call exec_builtin only if the command is builtin
*/
int		is_builtin(char *command, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->is_builtin[i] != NULL)
	{
		if (ft_strcmp(command, mini->is_builtin[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
////////////////////////////////////////////////////////////////////////////    Juntar estas dos funciones si no me paso de 25 lineas
/*
	Function to execute builtins

void	exec_builtin(char *command, t_mini *mini)
{ //Ver si tiene que ser ***args
	if (ft_strcmp("echo", command) == 0)
		ft_echo(mini);
	if (ft_strcmp("cd", command) == 0)
		ft_cd(mini);
	if (ft_strcmp("pwd", command) == 0)
		ft_pwd(mini);
	if (ft_strcmp("export", command) == 0)
		ft_export(mini);
	if (ft_strcmp("unset", command) == 0)
		ft_unset(mini);
	if (ft_strcmp("env", command) == 0)
		ft_env(mini);
	if (ft_strcmp("exit", command) == 0)
		ft_exit(mini);
}


int main(int argc, char **argv, char **envp) //Borrar este main cuando entregemos 
{
	t_mini	mini;
	init_mini(&mini, argv, envp);
	if (argc < 0)
		printf ("Error\n");
	//init_builtin(&mini);
	if ((is_builtin("env", &mini) == 1))
		exec_builtin("env", &mini);
	system("leaks -q minishell");
	return (0);
}*/