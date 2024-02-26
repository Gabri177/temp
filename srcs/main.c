/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:51 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 17:25:16 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_bool	is_ok(int arc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < arc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' && argv[i][j] < '0')
				return (FALSE);
			j ++;
		}
		i ++;
	}
	return (TRUE);
}

void	init_pro(t_pro *pro, t_philo *philos)
{
		pro->is_die = FALSE;
		pro->phis = philos;
		pthread_mutex_init (&pro->die_lock, NULL);
		pthread_mutex_init (&pro->eat_lock, NULL);
		pthread_mutex_init (&pro->wrt_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init (&forks[i], NULL);
		i ++;
	}
}

void	r_info(t_philo *phi, char **argv)
{
	phi->time_die = ft_atoi (argv[2]);
}

void	init_phis(t_pro *pro, pthread_mutex_t fork, char **argv)
{

}



int	main(int arc, char **argv)
{
	t_pro			project;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (arc != 5 && arc != 6)
		return (1);
	if (!is_ok (arc, argv))
		return (1);
	init_pro (&project, philos);
	init_forks (forks, ft_atoi (argv[1]));
	return (0);
}
