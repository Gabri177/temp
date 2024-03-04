/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ary.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:10:42 by javgao            #+#    #+#             */
/*   Updated: 2024/03/03 22:22:29 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init.h"

char	**ary2_cpy(t_mini mini)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc (sizeof (char *) * mini.argc);
	while (i < mini.argc - 1)
	{
		new[i] = ft_strdup (mini.argv[i + 1]);
		if (!new[i])
			return (NULL); //error
		i ++;
	}
	new[i] = NULL;
	return (new);
}
int	ary2_del(char **str, int index)
{
	int		len;
	char	*tem;

	len = 0;
	while (str[len])
		len ++;
	if (index >= len)
		return (FALSE);
	free (str[index]);
	str[index] = NULL;
	while (index < len)
	{
		str[index] = str[index + 1];
		index ++;
	}
	str [index] = NULL;
	return (TRUE);
}

int	is_grande(char *str)
{
	while (*str)
	{
		if (*str == '6')
			return (TRUE);
		str ++;
	}
	return (FALSE);
}

int	is_strsame(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (FALSE);
		s1 ++;
		s2 ++;
	}
	return (*s1 == *s2);
}

char	**ary_get_outfile(char **str)
{
	int		i;
	int		index;
	int		new_size;
	char	**new;

	i = 0;
	index = 0;
	new_size = 0;
	while (str[i])
	{
		if (is_grande (str[i]))
			new_size ++;
		i ++;
	}
	printf ("new_size: %d\n", new_size);
	new = malloc (sizeof (char *) * (new_size + 1));
	i = 0;
	while (str[i])
	{
		if (is_grande (str[i]) && is_strsame (str[i], "6"))
		{
			new[index ++] = str[i + 1];
			ary2_del (str, i);
			ary2_del (str, i + 1);
		}
		else if (is_grande (str[i]) && !is_strsame (str[i], "6"))
		{
			new[index ++] = str[i];
			ary2_del (str, i);
		}
		i ++;
	}
	new[index] = NULL;
	return new;
}

int	main(int argc, char **argv, char **envp)
{
	/*t_mini	mini;

	init_mini (&mini, arc, argv, envp);*/
	(void)envp;
	char	**test;
	char	**outfile;
	int		i = 0;
	t_mini	mini;

	mini.argc = argc;
	mini.argv = argv;
	test = ary2_cpy(mini);
	while (test[i])
	{
		printf ("eles : %s\n", test[i]);
		i ++;
	}
	i = 0;
	outfile = ary_get_outfile (test);
	while (outfile[i])
	{
		printf ("outfile : %s\n", outfile[i]);
		i ++;
	}
	return (0);
}
