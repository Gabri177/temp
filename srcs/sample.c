/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:59 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 16:05:00 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

typedef struct s_info
{
	pthread_mutex_t	l_num;
	pthread_mutex_t	l_test;
	int	num;
}	t_info;

void	*test(void *arg)
{
	int	i;
	t_info	*info;

	i = 0;
	info = (t_info *)arg;
	pthread_mutex_lock (&info->l_num);
	while (i < 1000000)
	{
		info->num += 1;
		i ++;
	}
	pthread_mutex_unlock (&info->l_num);
	pthread_mutex_lock (&info->l_test);
	printf ("this is a test \n");
	pthread_mutex_unlock (&info->l_test);
	return ((void *)arg);
}

int	main(void)
{
	pthread_t		th1;
	pthread_t		th2;
	t_info			info;

	info.num = 0;
	pthread_mutex_init (&info.l_num, NULL);
	pthread_mutex_init (&info.l_test, NULL);
	pthread_create (&th1, NULL, test, (void *)&info);
	pthread_create (&th2, NULL, test, (void *)&info);
	pthread_join (th1, NULL);
	pthread_join (th2, NULL);
	printf ("num: %d\n", info.num);

	return (0);
}
