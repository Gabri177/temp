/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ary_p_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <jjuarez-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:44:45 by yugao             #+#    #+#             */
/*   Updated: 2024/03/04 13:50:59 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test1(int a)
{
	printf ("test1 %d\n", a);
}

void	test2(int a)
{
	printf ("test1 %d\n", a);
}

void	test3(int a)
{
	printf ("test1 %d\n", a);
}

void	test4(int a)
{
	printf ("test1 %d\n", a);
}

int	main(void)
{
	typedef (*t_func_ary)(int);
	void	(*f[4])(int);

	f[0] = test1;
	f[1] = test2;
	f[2] = test3;
	f[3] = test4;
	f[0](1);
	f[1](2);
	f[2](3);
	f[3](4);
	t_func_ary	*test = (t_func_ary *) malloc (sizeof (t_func_ary) * 4);

	test[0] = test1;
	test[1] = test2;
	test[2] = test3;
	test[3] = test4;
	test[0](1);
	test[1](2);
	test[2](3);
	test[3](4);
	return (0);
}