/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arry_strs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:46:29 by yugao             #+#    #+#             */
/*   Updated: 2024/03/06 05:00:07 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//5555555555555
//释放字符串数组申请的内存, 包括每个元素和字符串数组的本身
void	arry_destory(char **ary)
{
	int	i;

	i = 0;
	if (!ary || !*ary)
		return ;
	while (ary[i])
	{
		free (ary[i]);
		i ++;
	}
	free (ary);
}

//输出ary这个字符串数组的元素值
void	arry_display(char **ary)
{
	int	i;

	i = 0;
	if (!ary || !*ary)
		return ;
	printf ("Argumentos Splited: \n\t{\n");
	while (ary[i])
	{
		printf ("\t\"%s\"", ary[i]);
		i ++;
		if (ary[i])
			printf (",\n");
	}
	printf ("\n\t}\n");
}

//如果val这个字符串不为空, 我们把他加入到字符串数组arys中, 并释放val内存, 让其指向NULL
// Si la cadena val no está vacía, la agregamos al arreglo de cadenas arys, 
//liberamos la memoria ocupada por val y hacemos que apunte a NULL.
void	arry_refresh(char ***arys, char **val)
{
	if (!*val)
		return ;
	if (**val != '\0')
		arry_add (arys, *val);
	free (*val);
	*val = NULL;
}

//初始化字符串数组, 让每个元素都指向NULL
void	arry_init(char **ary, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ary[i] = NULL;
		i ++;
	}
}

//通过数组中的值获取对应的index
// Obtener el índice correspondiente a través del valor en el arreglo.
int	arry_get_index(char **ary, char *val)
{
	int	i;

	i = 0;
	while (ary[i])
	{
		if (is_strsame (val, ary[i]))
			return (i);
		i ++;
	}
	return (-1);
}
