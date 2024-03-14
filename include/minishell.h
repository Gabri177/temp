/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:06:23 by javgao            #+#    #+#             */
/*   Updated: 2024/03/13 09:20:07 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <curses.h>
# include <term.h>
# include "parser.h"
# include "hash.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0
# define SINGLE 1
# define PIPESS 0
# define REDIRECT 1
# define APPEND 2
//===builtins===
# define NUM_BUILTINS 7
# define PROMPT "\x1b[1;32mminishell\x1b[0m\x1b[1;36m > \x1b[0m"

# define ERR0 "minishell: syntax error near unexpected token `newline'"
# define ERR1 "minishell: syntax error near unexpected token `>>'"
# define ERR2 "minishell: syntax error near unexpected token `<<'"
# define ERR3 "minishell: syntax error near unexpected token `<'"
# define ERR4 "minishell: syntax error near unexpected token `>'"
# define ERR5 "minishell: syntax error near unexpected token `|'"
# define INFILE "./Libft/ft_printf/.infile"
# define OUTFILE "./Libft/ft_printf/.outfile"

typedef int	t_bool;
typedef struct s_mini
{
	char	*line;
	char	**arg_ori;
	t_hash	*hash_env;
	char	**paths;
	char	**infile; //ABSOLUTE DIRECTION
	char	**outfile; //ABSOLUTE DIRECTION
	char	**commands; // "ls -l | hola echo dfd" ----> "ls -l" "|" "hola"
	char	***args; // "ls -l | hola echo dfd" ---> {""} {"echo" "dfd"}; 
	char	**cmds_and_args;
	int		is_echo_n; //Ver si hay que usar
	char	*is_builtin[NUM_BUILTINS + 1];
	int		argc;
	int		flag_output;
	int		flag_append_output;
	int		flag_unset_path;
	int		flag_here_doc;
	int		flag_input;
}			t_mini;

typedef struct s_cmd
{
	bool	found;
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_pipex
{
	int		size;
	int		infile;
	int		outfile;
	t_cmd	*cmds;
	int		**pipes;
	char	**paths;
	char	**argv;
	char	**envp;
	int		*child_pids;
	bool	heredoc;
	int		exitcode;
}	t_pipex;

int			g_sig;

/*	--------------------------- INIT --------------------------- */
void	init_mini(t_mini *mini, char **envp);
void	init_builtin(t_mini *mini);
void	init_env(t_mini *mini, char **envp);
void	shell_loop(t_mini *mini);
void	init_re(t_mini *mini);
int		clean_outfile(t_mini *mini);

/*	-------------------------- BUILTIN ---------------------------*/
int		is_builtin(char *command, t_mini *mini);
void	exec_builtin(char *command, char **arguments, t_mini *mini);
int		ft_echo(t_mini *mini, char **arguments, int flag);
int		ft_cd(t_mini *mini, char *argument);
int		ft_pwd(t_mini *mini);
int		ft_export(t_mini *mini, char *variable);
int		ft_unset(t_mini	*mini, char *variable);
int		ft_env(t_mini *mini);
int		ft_exit(char *line);

/*	-------------------------- EXECUTE ---------------------------*/
int		ft_execute(t_mini *mini);
int		single_command(t_mini *mini);
void	not_builtin(char	*command, char	**commands, t_mini *mini, int flag);
void	ft_exec_single(char *cmd, char **envp);
char	*join_args(char *command, char **arguments);
char	*ft_path(char *cmd, char **envp);
char	*ft_envp(char *variable, char **envp);
char	**check_cmds_and_args(t_mini *mini);
int		print(t_mini *mini);
void	open_all_files(t_mini *mini);
int		single_redir(t_mini *mini, char *command, char *input_file,
			char *output_file);

/*	-------------------------- HERE_DOC ---------------------------*/
int		single_here_doc(int argc, char **argv);
void	here_doc_consumer(char *cmd, char *arg1);
void	here_doc_producer(char *delimiter);
char	**parse_single_here_doc(t_mini *mini);

/*	--------------------------- ERROR ----------------------------*/
int		print_error(char *error);

/*	--------------------------- SIGNAL ---------------------------*/
void	init_sig(void);
void	init_sig_child(void);
/*	---------------------------- FREE ----------------------------*/
void	ft_free_four(char **one, char **two, char **three, char **four);
void	ft_free_arr(char **arr);

/*	---------------------------- UTILS ----------------------------*/
char	*ft_lower(char *str);
void	update_statu_write_outfile(t_mini *mini, char **outfile);
void	update_statu_write_dogii(t_mini *mini, char **infile);
/*	---------------------------- EXPAND ----------------------------*/
char	**split_filter(char **args, t_hash *hash);

/*	---------------------------- EXPAND ----------------------------*/
char	**split_filter(char **args, t_hash *hash);
char	*split_arg_filter(char *str, t_hash *hash);
void	args_add_var(char **str, t_hash *hash, char **new);

/*	---------------------------- APOYO ------------------------------*/
char	**filter_add_path(char **args_file, t_hash *hash);

/*	--------------------------- PIPEX --------------------------- */
/*	--------------------------- PIPEX --------------------------- */
/*	--------------------------- PIPEX --------------------------- */
/*	--------------------------- PIPEX --------------------------- */
/*	--------------------------- PIPEX --------------------------- */

/*	--------------------------- CHILD --------------------------- */
void	redirect(t_pipex pipex, int input, int output);
void	children(t_pipex pipex, int i);
void	child(t_pipex pipex, int i, int input, int output);

/*	--------------------------- ERROR --------------------------- */
void	error_message(char *file);
void	cmd_not_found(t_pipex *pipex, int i);

/*	--------------------------- FREE --------------------------- */
bool	close_all_fds(t_pipex *pipex);
bool	free_pipex(t_pipex *pipex);

/*	------------------------- HERE_DOC -------------------------- */
void	open_here_doc(t_pipex *pipex);
void	here_doc(t_pipex *pipex);

/*	--------------------------- MAIN --------------------------- */
int		pipex_bonus(t_mini *mini, int argc, char **argv, char **envp);
bool	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
bool	init_cmds(t_pipex *pipex);

/*	--------------------------- PARSE --------------------------- */
bool	is_command(t_pipex *pipex, char *command, int i);
void	find_command(t_pipex *pipex, int i);
void	find_paths(t_pipex *pipex);
void	open_files(t_pipex *pipex, t_mini *mini);
bool	parse_input(t_pipex *pipex, t_mini *mini);
void	g_sig_refresh(t_hash *hash, int new);

/*	--------------------------- PIPEX --------------------------- */
bool	create_pipes(t_pipex *pipex);
bool	wait_pids(t_pipex *pipex);
bool	allocate_pids(t_pipex *pipex);
bool	execute(t_pipex *pipex);

#endif
