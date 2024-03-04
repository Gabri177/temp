/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:34:33 by javgao            #+#    #+#             */
/*   Updated: 2024/03/03 21:17:21 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init.h"

void	init_mini(t_mini *mini, int argc, char **argv, char **envp)
{
	mini->argc = argc;
	mini->argv = argv;
	mini->envp = envp;
	mini->pwd = NULL; //Javi
	mini->old_pwd = NULL; //Javi
	mini->paths = NULL; //Javi
	mini->infile = NULL; //Gao
	mini->outfile = NULL; //Gao
	mini->commands = NULL; //Gao
	mini->args = NULL; //Gao
}

