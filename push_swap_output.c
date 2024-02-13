/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:28:39 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 08:41:33 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_puts(char *str)
{
	while (*str)
	{
		write (1, str, 1);
		str ++;
	}
}

void	ft_putnbr(int n)
{
	char	num;

	if (n == -2147483648)
		write (1, "-2147483648", 11);
	else if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
		ft_putnbr (n);
	}
	else
	{
		if (n < 10)
		{
			num = n + '0';
			write (1, &num, 1);
		}
		else
		{
			ft_putnbr (n / 10);
			ft_putnbr (n % 10);
		}
	}
}
