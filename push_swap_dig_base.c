/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_dig_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:56:16 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 10:08:01 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	is_zero_bit(int num, int p_bit)
{
	if ((num & (1 << p_bit)))
		return (FALSE);
	return (TRUE);
}

static int	ft_isspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	result;
	long	i;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace (str[i]))
		i ++;
	if (str[i] == '-')
	{
		sign = -1;
		i ++;
	}
	else if (str[i] == '+')
		i ++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		i ++;
	}
	return (result * sign);
}
