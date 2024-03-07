/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:20:49 by javgao            #+#    #+#             */
/*   Updated: 2024/03/06 20:09:46 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cd_no_arg(t_mini *mini)
{
	char	*home;
	char	*variable;
	char	*pwd;
	char	*oldpwd;

	if (hash_grep(mini->hash_env, "HOME") == NULL)
		return (print_error("cd: HOME not set"));
	else
	{
		home = ft_substr(hash_grep(mini->hash_env, "HOME"), 5, ft_strlen(hash_grep(mini->hash_env, "HOME")));
		pwd = ft_substr(hash_grep(mini->hash_env, "PWD"), 4, ft_strlen(hash_grep(mini->hash_env, "PWD")));
		variable = ft_strjoin("PWD=", home);
		oldpwd = ft_strjoin("OLDPWD=", pwd);
		ft_export(mini, variable);
		ft_export(mini, oldpwd);
		free(home);
		free (variable);
		free(oldpwd);
		free(pwd);
	}
	return (EXIT_SUCCESS);
}

static int	cd_dot_dot(t_mini *mini)
{
	char	*oldpwd;
	char	*newpwd;
	char	*newoldpwd;

	oldpwd = ft_substr(hash_grep(mini->hash_env, "PWD"), 4, ft_strlen(hash_grep(mini->hash_env, "PWD")));
	newpwd = ft_substr(hash_grep(mini->hash_env, "PWD"), 0, ft_strrchrlen(hash_grep(mini->hash_env, "PWD"), '/'));
	newoldpwd = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(mini, newpwd);
	ft_export(mini, newoldpwd);
	free (oldpwd);
	free(newpwd);
	free(newoldpwd);
	return(EXIT_FAILURE);
}

int	ft_cd(t_mini *mini, char *argument)
{
	if (argument == NULL || !*argument)
		return (cd_no_arg(mini));
	else if (ft_strcmp(argument, "..") == 0)
		return(cd_dot_dot(mini));
	else if (argument[0] == '.')
		return (EXIT_SUCCESS);
	//else 								-----------------------------------------//Me falta tener en cuenta esto
	//	cd_word()
	return (EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////// cd should update PWD and OLD_PWD ENV esto lo haré con las funciones export

/*int	main(int argc, char **argv, char **envp)				//Con leaks
{
	t_mini 	mini;
	argc = 0;
	argv = NULL;
	init_env(&mini, envp);
	hash_display(*mini.hash_env);
	ft_cd(&mini, "..");
	hash_display(*mini.hash_env);
	hash_destory(mini.hash_env);
	system("leaks -q minishell");
	return (0);
}*/