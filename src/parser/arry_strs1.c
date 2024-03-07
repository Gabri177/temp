/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arry_strs1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:46:36 by yugao             #+#    #+#             */
/*   Updated: 2024/03/07 22:06:01 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//555555555
//计算字符串数组的大小, 因为字符串数组的结尾元素是NULL, 用来判断是否已经结束
int	arry_count(char **arys)
{
	int	i;

	i = 0;
	if (!arys || !*arys)
		return (0);
	while (arys[i])
		i ++;
	return (i);
}

//我们这个函数不单单是对原字符串数组的拷贝, 我们申请多一个空间, 然后将原来的字符串数组销毁
// Esta función no es simplemente una copia del arreglo de cadenas original.
//Nosotros solicitamos un espacio adicional y luego destruimos el arreglo de cadenas original.
static char	**arry_cpy(char **ary)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc (sizeof (char *) * (arry_count (ary) + 2));
	if (!new)
		return (NULL);
	arry_init (new, (arry_count (ary) + 2));
	while (i < arry_count (ary))
	{
		new[i] = strdup (ary[i]);
		i ++;
	}
	arry_destory (ary);
	return (new);
}

//给字符串数组arys添加新的字符串元素val, 我们通过复制函数扩容1个单位, 然后加入新元素
//在复制函数中我们销毁了复制之前的字符串数组, 我们释放了内存
//在使用这个函数前 要先创建一个char**类型的指针并初始化
// Para agregar un nuevo elemento de cadena val al arreglo de cadenas arys, expandimos el 
//arreglo en una unidad mediante una función de copia, y luego agregamos el nuevo elemento.
// Dentro de la función de copia, destruimos el arreglo de cadenas original y liberamos la memoria.
// Antes de usar esta función, es necesario crear primero un puntero de tipo char** e inicializarlo.
int	arry_add(char ***arys, char *val)
{
	int	i;

	i = 0;
	if (!*arys)
	{
		*arys = malloc (sizeof (char *) * 2);
		if (!*arys)
			return (FALSE);
		(*arys)[0] = strdup (val);
		(*arys)[1] = NULL;
		return (TRUE);
	}
	*arys = arry_cpy (*arys);
	while ((*arys)[i])
		i ++;
	(*arys)[i] = strdup (val);
	return (TRUE);
}

//这里我们不仅仅复制, 新数组的大小比原来数组小1个单位
// Aquí no solo copiamos, el tamaño del nuevo arreglo es un elemento menor que el arreglo original.
static char	**arry_cpy_sml(char **args)
{
	char	**new;
	int		i;
	int		len;

	i = 0;
	len = arry_count (args);
	if (len == 0)
		return (NULL);
	new = malloc (sizeof (char *) * len);
	if (!new)
		return (NULL);
	arry_init (new, len);
	while (i < len - 1)
	{
		new[i] = strdup (args[i]);
		if (!new[i])
			return (NULL);
		i ++;
	}
	arry_destory (args);
	return (new);
}

//删除数组中指定位置的元素
// Eliminar el elemento en una posición específica del arreglo.
int	arry_del(char ***args, int index)
{
	//int		i; //Unused variable
	//char	*tem; //Unused variable
	int	len;

	//printf ("----这里是删除数组元素的函数内部， 我们开始计算数组长度\n");
	len = arry_count (*args);
	//printf ("----这里是删除数组元素的函数内部， 我们计算出的数组长度 %d\n", len);
	if (index >= len || index < 0)
		return (FALSE);
	if (len == 1)
	{
		free ((*args)[index]);
		(*args)[index] = NULL;
		free (*args);
		return (TRUE);
	}
	free ((*args)[index]);
	(*args)[index] = NULL;
	//printf ("----这是删除数组元素函数的内部， 我们刚刚释放了index位置的数组元素, 并把这个位置指向了NULL \n");
	while (index < len - 1)
	{
		(*args)[index] = (*args)[index + 1];
		index ++;
	}
	(*args)[index] = strdup ("trash");
	*args = arry_cpy_sml (*args);
	//printf ("----我们成功删除了index位置的数组元素！\n");
	return (TRUE);
}
