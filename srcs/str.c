/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:05:02 by yugao             #+#    #+#             */
/*   Updated: 2024/02/28 21:41:31 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static size_t	str_len(const char *str)
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

void	msg(char *str, t_philo *phi)
{
	size_t	time;

	pthread_mutex_lock (phi->l_wrt);
	time = gettime () - phi->time_begin;
	if (!check_dead (phi))
		printf ("%zu\tPhilosopher[%d] %s\n", time, phi->id, str);
	pthread_mutex_unlock (phi->l_wrt);
}
