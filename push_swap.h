/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:49:10 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 10:09:19 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define TRUE 1
# define FALSE 0
# define ERR_REPETIR 1
# define ERR_LETRA 2
# define ERR_READ 3

typedef struct s_list
{
	int				num;
	int				index;
	struct s_list	*front;
	struct s_list	*last;
}	t_list;

typedef int	t_bool;
typedef int	t_err;

//---LIST---
t_bool	l_fresh_index(t_list *l);
t_list	*l_new(int val);
int		l_len(const t_list *l);
t_bool	l_add_front(t_list **l, int val);
t_bool	l_add_tail(t_list **l, int val);
t_bool	l_print(t_list *l);
t_list	*l_grep_index(t_list *l, int index);
t_bool	l_swap(t_list **l, int index1, int index2);
t_bool	l_destory(t_list **l);
t_bool	l_isorden(t_list *l);
t_bool	l_rotate_nom(t_list *l, int *num_pa);
t_bool	l_rotate_rev(t_list *l, int *num_pa);
t_bool	l_push(t_list **l1, t_list **l2, t_bool isa, int *ispa);
t_bool	l_swap_index(t_list *l, int i1, int i2);
t_bool	l_sort(t_list *l);
t_bool	l_copy(t_list *ori, t_list **new);
t_list	*l_grep_val(t_list *l, int val);
t_bool	l_neg_to_pos(t_list *ref, t_list *ori);
//---LIST---

t_bool	is_zero_bit(int num, int p_bit);
long		ft_atoi(const char *str);
void	sol_pa_pb(int num_pa);
void	solucion(t_list *ori, t_list *asis);

void	arc_check(int arc, t_list **ori, t_list **cpy, t_list **asis);
t_bool	num_check(char *str);
t_bool	rept_check(t_list *l);
void	err_control(t_list **l, t_err type);

void	ft_puts(char *str);
void	ft_putnbr(int n);
#endif