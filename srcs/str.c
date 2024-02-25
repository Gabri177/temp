/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:05:02 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 17:25:28 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

size_t	str_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len ++;
	return (len);
}

void	str_errmsg(const char *msg)
{
	write (2, msg, str_len (msg));
}

void	str_msg(const char *msg)
{
	write (1, msg, str_len (msg));
}