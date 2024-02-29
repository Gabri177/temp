/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:57:41 by yugao             #+#    #+#             */
/*   Updated: 2024/02/28 22:21:41 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"


t_bool	init_prj(t_pro *pro, t_philo *philos)
{
	pro->is_die = FALSE;
	pro->phis = philos;
	if (pthread_mutex_init (&pro->wrt_lock, NULL))
		return (FALSE);
	if (pthread_mutex_init (&pro->die_lock, NULL))
		return (FALSE);
	if (pthread_mutex_init (&pro->eat_lock, NULL))
		return (FALSE);
	return (TRUE);
}

t_bool	init_forks(t_lock *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init (&forks[i], NULL))
			return (FALSE);
		i ++;
	}
	return (TRUE);
}

static void	init_r_info(t_philo *phi, char **argv)
{
	phi->n_philo = ft_atoi (argv[1]);
	phi->time_die = ft_atoi (argv[2]);
	phi->time_eat = ft_atoi (argv[3]);
	phi->time_slp = ft_atoi (argv[4]);
	phi->time_last_eat = gettime ();
	phi->time_begin = gettime ();
	if (argv[5])
		phi->n_must_eat = ft_atoi (argv[5]);
	else
		phi->n_must_eat = -1;
	phi->n_eated = 0;
}

void	init_phis(t_pro *pro, t_lock *fork, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi (argv[1]))
	{
		pro->phis[i].id = i + 1;
		pro->phis[i].n_eated = 0;
		pro->phis[i].l_wrt = &pro->wrt_lock;
		pro->phis[i].l_lfork = &fork[i];
		pro->phis[i].l_rfork = &fork[(i + 1) % ft_atoi (argv[1])];
		pro->phis[i].isdie = &pro->is_die;
		pro->phis[i].l_die = &pro->die_lock;
		pro->phis[i].l_eat = &pro->eat_lock;
		pro->phis[i].iseating = FALSE;
		init_r_info (&pro->phis[i], argv);
		i ++;
	}
}
