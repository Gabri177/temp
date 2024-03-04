#include "../include/minishell.h"

t_bool	my_echo(char **argv)
{

}

t_bool	my_cd(char **argv)
{

}

t_bool	my_pwd(char **argv)
{
	(void)argv;
}

t_bool	my_export(char **argv)
{

}

t_bool	my_unset(char **argv)
{

}

t_bool	my_env(char **argv)
{

}

t_bool	my_exit(char **argv)
{

}

t_fucs	*init_funcs(void)
{
	t_fucs	*funcs;

	funcs = malloc (sizeof (t_fucs) * 7);
	if (!funcs)
		printf ("error");//Error;
	funcs[0] = my_echo;
	funcs[1] = my_cd;
	funcs[2] = my_pwd;
	funcs[3] = my_export;
	funcs[4] = my_unset;
	funcs[5] = my_env;
	funcs[6] = my_exit;
	return (funcs);
}
// luego se puede llamar a cada funcione de esta manera  var[index](argumento);
// pero andes tenemos que crear una variable del tipo t_fucs.
// al terminar usar lo hay que liberar esta variable
// de esta manera supongo que no hace falta poner todas las funciones en el header solo init_funcs ya suficiente