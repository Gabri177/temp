/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:16 by javgao            #+#    #+#             */
/*   Updated: 2024/03/07 23:04:54 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void shell_loop(t_mini *mini) 
{
	char *line;

	while (1) 
	{
		line = readline("mi_shell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			mini->arg_ori = arg_abordar (line);
			free(line);
			line = NULL;
			//printf ("original :\n");
			//arry_display (mini->arg_ori);
			mini->outfile = args_to_outfile (&mini->arg_ori);
			//printf ("outfile :\n");
			//arry_display (mini->outfile);
			mini->commands = args_to_cmds (&mini->arg_ori);
			printf ("command :\n");
			arry_display (mini->commands);
			arry_display (mini->arg_ori);
			mini->args = args_to_args (&mini->arg_ori);
			printf ("ARGSSSSSSS :\n");
			argss_display(mini->args);
			//excuter
		}
		
		arry_destory (mini->arg_ori);
		mini->arg_ori = NULL;
		arry_destory (mini->outfile);
		mini->outfile = NULL;
		arry_destory (mini->commands);
		mini->commands = NULL;
		argss_destory (mini->args);
		mini->args = NULL;
		// Aquí se pueden añadir códigos para procesar el comando
	}
}

/*int main() {
    // Inicialización de la biblioteca readline
    rl_on_new_line();
    shell_loop(); // Ejecutar el bucle del shell
    return 0;
}*/