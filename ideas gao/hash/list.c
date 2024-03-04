/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:30:18 by yugao             #+#    #+#             */
/*   Updated: 2024/03/03 01:39:33 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hash.h"

t_node	*list_init(void)
{
	t_node	*new;

	new = malloc (sizeof (t_node));
	if (!new)
		return (NULL);
	new->id = -1;
	new->key = NULL;
	new->val = NULL;
	new->next = NULL;
	return (new);
}

t_bool	list_push(t_node *l, char *key, char *val)
{
	t_node	*new_node;
	t_node	*current;

	current = l;
	new_node = list_init ();
	if (!new_node)
		return (FALSE);
	new_node->key = ft_strdup (key);
	new_node->val = ft_strdup (val);
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (TRUE);
}

t_bool	list_del(t_node *l, char *key)
{
	t_node	*current;
	t_node	*prev;

	if (!l || !l->next)
		printf ("The list is empty!\n");
	prev = l;
	current = prev->next;
	while (current)
	{
		if (is_strsame (key, current->key))
		{
			prev->next = current->next;
			free (current);
			return (TRUE);
		}
		prev = current;
		current = current->next;
	}
	return (FALSE);
}

t_bool	list_grep(t_node *l, char *key)
{
	t_node	*tem;

	if (!l || !l->next)
	{
		printf ("No element to find out!\n");
		return (FALSE);
	}
	else
	{
		tem = l->next;
		while (tem)
		{
			if (is_strsame (key, tem->key))
			{
				printf ("GREP:\n\tKEY:%s VAL:%s ID:%d\n", tem->key, tem->val, tem->id);
				return (TRUE);
			}
			tem = tem->next;
		}
	}
	return (FALSE);
}

t_bool	list_destory(t_node *l)
{
	t_node	*cur;
	t_node	*trash;

	if (!l || !l->next)
		return (TRUE);
	cur = l->next;
	trash = NULL;
	while (cur)
	{
		trash = cur;
		cur = cur->next;
		if (trash->val)
			free (trash->val);
		if (trash->key)
			free (trash->key);
		free (trash);
	}
	free (l);
	l = NULL;
	return (TRUE);
}
void	list_print(t_node *l)
{
	t_node	*tem;
	int		num;

	num = 0;
	if (!l || !l->next)
		printf ("The list is empty!\n");
	tem = l->next;
	while (tem)
	{
		printf ("%d:\tKEY:%s VAL:%s ID:%d\n", num, tem->key, tem->val, tem->id);
		num ++;
		tem = tem->next;
	}
}
