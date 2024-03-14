/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:24:12 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 23:08:56 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_envp(char *variable, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, variable) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*ft_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*path;
	char	**cmds;

	i = -1;
	paths = ft_split(ft_envp("PATH", envp), ":");
	cmds = ft_split(cmd, " ");
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path, cmds[0]);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_arr(cmds);
			return (exec);
		}
		free(exec);
	}
	ft_free_arr(paths);
	ft_free_arr(cmds);
	return (cmd);
}

void	ft_exec_single(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	int		status;
	pid_t	pid;

	cmds = ft_split(cmd, " ");
	path = ft_path(cmds[0], envp);
	pid = fork();
	if (pid == 0)
	{
		init_sig_child ();
		if (execve(path, cmds, envp) == -1)
		{
			printf ("mini: %s: command not found\n", cmd);
			exit(0);
		}
	}
	else if (pid < 0)
		print_error("fork failed");
	else
	{
		waitpid(pid, &status, 0);
		g_sig = WIFEXITED (status);
	}
}

int	single_command(t_mini *mini)
{
	char	**here_doc;

	if (is_builtin(mini->commands[0], mini) == TRUE)
		exec_builtin(mini->commands[0], mini->args[0], mini);
	else
	{
		if (mini->flag_unset_path == TRUE)
			return (print_error("No such file or directory"));
		if (mini->flag_here_doc == TRUE)
		{
			here_doc = parse_single_here_doc(mini);
			single_here_doc(3, here_doc);
			ft_free_arr(here_doc);
		}
		not_builtin(mini->commands[0], mini->args[0], mini, SINGLE);
	}
	return (TRUE);
}
