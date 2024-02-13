/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:36:57 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 22:55:14 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sol_pa_pb(int num_pa)
{
	int	i;

	i = 0;
	if (num_pa == 0)
		return ;
	if (num_pa < 0)
	{
		while (i < -num_pa)
		{
			ft_puts ("pa\n");
			i ++;
		}
		return ;
	}
	while (i < num_pa)
	{
		ft_puts ("pb\n");
		i ++;
	}
	return ;
}

t_bool	sol_tres(t_list *ori)
{
	int	basura;

	basura = 0;
	if (l_grep_index (ori, 0)->num == 0 && l_grep_index (ori, 1)->num == 2)
		return (l_sa (ori), l_rotate_nom (ori, &basura));
	else if (l_grep_index (ori, 0)->num == 1 && l_grep_index (ori, 1)->num == 0)
		return (l_sa (ori));
	else if (l_grep_index (ori, 0)->num == 1 && l_grep_index (ori, 1)->num == 2)
		return (l_rotate_rev(ori, &basura));
	else if (l_grep_index (ori, 0)->num == 2 && l_grep_index (ori, 1)->num == 1)
		return (l_sa (ori), l_rotate_rev (ori, &basura));
	else if (l_grep_index (ori, 0)->num == 2 && l_grep_index (ori, 1)->num == 0)
		return (l_rotate_rev(ori, &basura));
	return (TRUE);
}

void	solucion(t_list *ori, t_list *asis)
{
	int	num_bit;
	int	len;
	int	ispa;

	ispa = 0;
	num_bit = 0;
	while (!l_isorden (ori) || l_len (asis))
	{
		len = l_len(ori);
		while (len --)
		{
			if (is_zero_bit (l_grep_index (ori, 0)->num, num_bit))
				l_push (&ori, &asis, TRUE, &ispa);
			else
				l_rotate_nom (ori, &ispa);
			if (l_isorden (ori) && !l_len (asis))
				break ;
		}
		num_bit ++;
		while (l_len (asis))
			l_push (&asis, &ori, FALSE, &ispa);
	}
	sol_pa_pb (ispa);
	l_destory (&ori);
}

int	main(int arc, char **argv)
{
	int		i;
	t_list	*ori;
	t_list	*cpy;
	t_list	*asis;

	i = 1;
	arc_check (arc, &ori, &cpy, &asis);
	while (i < arc)
	{
		if (!num_check(argv[i]) || ft_atoi (argv[i]) > INT_MAX
			|| ft_atoi (argv[i]) < INT_MIN)
			err_control (&ori, ERR_LETRA);
		if (!l_add_tail (&ori, ft_atoi (argv[i])))
			err_control (&ori, ERR_READ);
		i ++;
	}
	l_copy (ori, &cpy);
	l_sort (cpy);
	if (!rept_check (cpy))
		err_control (&ori, ERR_REPETIR);
	l_neg_to_pos (cpy, ori);
	if (arc <= 4)
		sol_tres (ori);
	solucion (ori, asis);
	return (0);
}
