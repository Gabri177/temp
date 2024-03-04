/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:06:23 by javgao            #+#    #+#             */
/*   Updated: 2024/03/03 19:28:23 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

//typedef int	t_bool;
//typedef		(*t_fucs)(char **argv);

typedef struct s_mini
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
	char	**paths;
	char	*infile; //ABSOLUTE DIRECTION
	char	**outfile; //ABSOLUTE DIRECTION
	char	**commands;
	char	***args;
}			t_mini;

#endif