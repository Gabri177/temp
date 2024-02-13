/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_error_control.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:28:33 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 12:18:13 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	arc_check(int arc, t_list **ori, t_list **cpy, t_list **asis)
{
	if (arc == 1)
		exit (EXIT_FAILURE);
	*ori = NULL;
	*cpy = NULL;
	*asis = NULL;
}

t_bool	num_check(char *str)
{
	if (!str || !*str)
		return (FALSE);
	if (*str == '-')
		str ++;
	while (*str)
	{
		if ((*str < '0' || *str > '9'))
			return (FALSE);
		str ++;
	}
	if (*(str - 1) == '-')
		return (FALSE);
	return (TRUE);
}

t_bool	rept_check(t_list *l)
{
	t_list	*head;

	head = l;
	if (!l)
	{
		l_destory (&l);
		return (FALSE);
	}
	while (l->last)
	{
		if (l->num == l->last->num)
		{
			l_destory (&head);
			return (FALSE);
		}
		l = l->last;
	}
	return (TRUE);
}

void	err_control(t_list **l, t_err type)
{
	char	*error_message;

	error_message = "Error\n";
	if (type == ERR_READ)
		write(2, error_message, 6);
	else if (type == ERR_LETRA)
		write(2, error_message, 6);
	else if (type == ERR_REPETIR)
		write(2, error_message, 6);
	if (l_len (*l) != 0)
		l_destory (l);
	exit (EXIT_FAILURE);
}
