#include "../include/minishell.h"

#define TOK_SPLIT " \t\r\n"
#define BUFFERSIZE 64

int	my_cd(char **tokens);
int	my_help(char **tokens);
int	my_exit(char **tokens);



int	(*bultin_func[])(char **) =
	{
		&my_cd,
		&my_help,
		&my_exit
	};

char	*bultin_cmd[] =
	{
		"cd",
		"help",
		"exit"
	};

int	minishell_bultin_nums(void)
{
	return (sizeof (bultin_cmd) / sizeof (bultin_cmd[0]));
}

int	my_cd(char **tokens)
{
	if (tokens[1] == NULL)
		printf ("no dir!\n");
	else
	{
		if (chdir (tokens[1]) != 0)
			printf ("no puede cambiar la dir!\n");
	}
	return 1;
}

int	my_help(char **tokens)
{
	puts ("this is minishell");
	for (int i = 0; i < minishell_bultin_nums (); i ++)
	{
		printf ("%s\n", bultin_cmd[i]);
	}
	return 1;
}

int	my_exit(char **tokens)
{
	return 0;
}
char	*minishell_read_line()
{
	char	*line = NULL;
	size_t	bufsize = 0;

	getline (&line, &bufsize, stdin);
	return (line);
}

//parsing
char	**minishell_split_line(char *line)
{
	int	buffer_size = BUFFERSIZE;
	int	position = 0;
	char **tokens = malloc (buffer_size * sizeof (char *));
	char *token;

	token = strtok (line, TOK_SPLIT);
	while (token != NULL)
	{
		tokens[position ++] = token;
		token = strtok (NULL, TOK_SPLIT);
	}
	tokens[position] = NULL;
	return (tokens);
}
int	minishell_launch(char **tokens)
{
	pid_t	pid, wpid;
	int		status;

	pid = fork ();
	if (pid == 0)
	{
		if (execvp (tokens[0], tokens) == -1)
			printf ("ejecutar comando error!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			wpid = waitpid (pid, &status, WUNTRACED);
		} while(!WIFEXITED (status) && !WIFSIGNALED (status));
		/*
			pid_t waitpid(pid_t pid, int *status, int options);
			Éxito: devuelve el ID del proceso hijo esperado; Falla: -1
			En el campo options, usamos WUNTRACED, lo que significa que si el proceso hijo entra en estado de pausa, regresará inmediatamente, pero no se tomará en cuenta el estado de finalización del hijo.
			Nuestra evaluación del código de estado se escribe dentro de este bucle while:
			while(!WIFEXITED(status) && !WIFSIGNALED(status))
			donde:

			WIFEXITED(status) si este valor es no cero indica que el proceso terminó normalmente.
			Si el macro anterior es verdadero, en este momento se puede obtener el estado de salida del proceso a través de WEXITSTATUS(status) (el argumento al salir).
			WIFSIGNALED(status) es no cero indica que el proceso terminó anormalmente.
			Si el macro anterior es verdadero, en este momento se puede obtener el número de señal que hizo que el proceso terminara a través de WTERMSIG(status).
			Podemos reescribir nuestro bucle while como:
			while(!WIFEXITED(status) && !WIFSIGNALED(status)) es equivalente a
			while(!(WIFEXITED(status) || WIFSIGNALED(status)))
			Para que el bucle while continúe ejecutándose,
			necesitamos !(WIFEXITED(status) || WIFSIGNALED(status)) = 1
			es decir, (WIFEXITED(status) || WIFSIGNALED(status)) = 0
			Esto indica que nuestro proceso hijo no ha terminado normalmente, pero tampoco ha terminado anormalmente, lo que significa que el proceso hijo aún está en ejecución.
			Por lo tanto, nuestro proceso padre necesita esperar en un bucle.
		*/
	}
	return 1;
}

int	minishell_execute(char **tokens)
{
	if (tokens[0] == NULL)
		return (1);
	for (int i = 0; i < minishell_bultin_nums (); i ++)
	{
		if (strcmp (tokens[0], bultin_cmd[i]) == 0)
			return (bultin_func[i](tokens));
	}
	return (minishell_launch (tokens));
}

void	event_loop(void)
{
	char	*line;
	char	**split;
	int		status;

	do
	{
		char path[100];
		getcwd (path, 100);
		char	now[200] = "[Minishell ";
		strcat (now, path);
		strcat (now, " ]$");
		printf ("%s", now);
		line = minishell_read_line ();
		split = minishell_split_line (line);
		status = minishell_execute (split);

		free (line);
		free (split);
	} while(status);

}

int	main(int arc, char **argv)
{
	event_loop ();
	return (0);
}