/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:05:06 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 16:05:07 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

size_t	gettime(void)
{
	t_timeval	time;

	if (gettimeofday (&time, NULL) == -1)
		str_errmsg ("Can not get the current time! \n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(size_t m_time)
{
	size_t	tem_t;

	tem_t = gettime ();
	while (gettime() - tem_t < m_time)
		usleep (500);
}

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int				i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}
