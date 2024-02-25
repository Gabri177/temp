/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:05:04 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 17:25:47 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* void	do_eat(t_philo	*phi)
{
	pthread_mutex_lock (&phi->l_lfork);
	printf ("philosopher %d grabe the left fork...\n", phi->id);
	pthread_mutex_lock (&phi->l_rfork);
	printf ("philosopher %d grabe the right fork...\n", phi->id);
	ft_sleep (phi->time_eat);
	pthread_mutex_lock (&phi->l_eat);
	phi->n_eated ++;
	printf ("philosopher %d is eating...\n", phi->id);
	ft_sleep (phi->time_eat);
	phi->time_last_eat = gettime ();
	pthread_mutex_unlock (&phi->l_eat);
	pthread_mutex_unlock (&phi->l_lfork);
	pthread_mutex_unlock (&phi->l_rfork);
}

void	do_slp(t_philo	*phi)
{
	printf ("philosopher %d is sleeping...\n", phi->id);
	ft_sleep (phi->time_slp);
}

void	do_thk(t_philo	*phi)
{
	printf ("philosopher %d is thinking...\n", phi->id);
}

t_bool	t_creat_philo(int arc, char **argv, t_philo *phi)
{
	int		i;

	i = 0;
	phi = (t_philo *) malloc (sizeof (t_philo) * ft_atoi (argv[1]));
	if (!phi)
		return (FALSE);
	while (i < ft_atoi (argv[1]))
	{
		phi[i].id = i;
		phi[i].n_philo = ft_atoi (argv[1]);
		phi[i].time_die = ft_atoi (argv[2]);
		phi[i].time_eat = ft_atoi (argv[3]);
		phi[i].time_slp = ft_atoi (argv[4]);
		phi[i].time_last_eat = gettime ();
		if (arc == 6)
			phi[i].n_must_eat = ft_atoi (argv[5]);
		else
			phi[i].n_must_eat = -1;
		phi[i].n_eated = 0;
		i ++;
	}
	i = 0;
	while (i < phi[0].n_philo)
	{
		pthread_mutex_init (&phi[i].l_eat, NULL);
		pthread_mutex_init (&phi[i].l_lfork, NULL);
		pthread_mutex_init (&phi[i].l_rfork, NULL);
		pthread_mutex_init (&phi[i].l_slp, NULL);
		pthread_mutex_init (&phi[i].l_prt, NULL);
		pthread_create (&phi[i].thread, NULL, philo_do, (void *)&phi[i]);
		i ++;
	}
	i = 0;
	while (i < phi[0].n_philo)
	{
		pthread_join(phi[i].thread, NULL);
		i++;
	}
	return (TRUE);
}

void	*philo_do(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	do_eat (phi);
	do_slp (phi);
	do_thk (phi);
	return (arg);
} */
