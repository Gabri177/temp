/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arry_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:30:31 by yugao             #+#    #+#             */
/*   Updated: 2024/03/05 01:01:20 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 比较两个字符串是不是完全相等, 包括\0, 如果相等返回真
// Comparar si dos cadenas son completamente iguales, incluyendo el
// carácter '\0'. Si son iguales, devuelve verdadero.
int	is_strsame(char *s1, char *s2)
{
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