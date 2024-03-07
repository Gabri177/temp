/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:20:49 by javgao            #+#    #+#             */
/*   Updated: 2024/03/06 14:11:17 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_mini *mini, char *variable)
{
	int		len_to_equal;
	char	*key;

	len_to_equal = ft_strchrlen(variable, '=');
	key = ft_substr(variable, 0, len_to_equal);
	hash_push(mini->hash_env, key, variable);
	free(key);
	return (EXIT_SUCCESS);
}

/*int main(int argc, char **argv, char **envp)			//Tiene leaks que estoy haciendo mal gao???????
{
	t_mini	mini;
	argc = 0;
	argv = NULL;
	init_env(&mini, envp);
	char variable[] = "PWD=home";
	ft_export(&mini, variable);
	hash_display(*mini.hash_env);
	hash_destory(mini.hash_env);
	system ("leaks -q minishell");
	return (0);
}*/