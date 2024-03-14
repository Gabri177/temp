/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:20:49 by javgao            #+#    #+#             */
/*   Updated: 2024/03/10 01:39:17 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*pwd;

	pwd = ft_substr(hash_grep(mini->hash_env, "PWD"), 4,
			ft_strlen(hash_grep(mini->hash_env, "PWD")));
	printf ("%s\n", pwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
