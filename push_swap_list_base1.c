/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_list_base1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:54:20 by yugao             #+#    #+#             */
/*   Updated: 2024/02/12 01:23:15 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	l_fresh_index(t_list *l)
{
	int	diff;

	if (!l)
		return (FALSE);
	diff = 0 - l->index;
	while (l)
	{
		l->index = l->index + diff;
		l = l->last;
	}
	return (TRUE);
}

t_list	*l_new(int val)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof (t_list));
	if (!new)
		return (FALSE);
	new->front = NULL;
	new->last = NULL;
	new->num = val;
	new->index = 0;
	return (new);
}

int	l_len(const t_list *l)
{
	int	len;

	len = 0;
	if (!l)
		return (0);
	while (l)
	{
		len ++;
		l = l->last;
	}
	return (len);
}

t_bool	l_add_front(t_list **l, int val)
{
	t_list	*new;

	if (!l)
		return (FALSE);
	new = l_new (val);
	if (!new)
		return (FALSE);
	if (!(*l))
		*l = new;
	else
	{
		(*l)->front = new;
		new->last = (*l);
		new->index = (*l)->index - 1;
		*l = new;
	}
	l_fresh_index (*l);
	return (TRUE);
}

t_bool	l_add_tail(t_list **l, int val)
{
	t_list	*new;
	t_list	*tem;

	new = l_new (val);
	if (!new)
		return (FALSE);
	if (!l)
		return (FALSE);
	if (!(*l))
		*l = new;
	else
	{
		tem = *l;
		while (tem->last)
			tem = tem->last;
		tem->last = new;
		new->front = tem;
		new->index = tem->index + 1;
	}
	l_fresh_index (*l);
	return (TRUE);
}
