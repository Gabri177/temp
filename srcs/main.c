/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:51 by yugao             #+#    #+#             */
/*   Updated: 2024/02/26 22:20:40 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_bool	is_ok(int arc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < arc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (FALSE);
			j ++;
		}
		i ++;
	}
	return (TRUE);
}

void	init_prj(t_pro *pro, t_philo *philos)
{
	pro->is_die = FALSE;
	pro->phis = philos;
	pthread_mutex_init (&pro->die_lock, NULL);
	pthread_mutex_init (&pro->eat_lock, NULL);
	pthread_mutex_init (&pro->wrt_lock, NULL);
}

void	init_forks(t_lock *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init (&forks[i], NULL);
		i ++;
	}
}

void	init_r_info(t_philo *phi, char **argv)
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
		pro->phis[i].l_eat = &pro->eat_lock;
		pro->phis[i].l_die = &pro->die_lock;
		pro->phis[i].l_lfork = &fork[i];
		pro->phis[i].l_rfork = &fork[(i + 1) % ft_atoi (argv[1])];
		pro->phis[i].isdie = &pro->is_die;
		init_r_info (&pro->phis[i], argv);
		i ++;
	}
	// i = 0;
	// while (i < ft_atoi (argv[1]))
	// {
	// 	printf ("time1 : %zu, time2: %zu\n", pro->phis[i].time_last_eat, pro->phis[i].time_begin);
	// 	i ++;
	// }
}
void	msg(char *str, t_philo *phi)
{
	size_t	time;

	pthread_mutex_lock (phi->l_wrt);
	time = gettime () - phi->time_begin;
	if (*phi->isdie != TRUE)
		printf ("%zu\tPhilosopher[%d] %s\n", time, phi->id, str);
	pthread_mutex_unlock (phi->l_wrt);
}
void	eat(t_philo *phi)
{
	//printf ("eat\n");
	pthread_mutex_lock (phi->l_rfork);
	msg ("has taken a fork", phi);
	if (phi->n_philo == 1)
	{
		ft_sleep (phi->time_die);
		pthread_mutex_unlock (phi->l_rfork);
		return ;
	}
	pthread_mutex_lock (phi->l_lfork);
	msg ("has taken a fork", phi);
	msg ("is eating", phi);
	ft_sleep (phi->time_eat);
	phi->n_eated ++;
	phi->time_last_eat = gettime ();
	pthread_mutex_unlock(phi->l_lfork);
	pthread_mutex_unlock(phi->l_rfork);
}
void	slp(t_philo *phi)
{
	msg ("is sleeping", phi);
	ft_sleep (phi->time_slp);
}
void	thk(t_philo *phi)
{
	msg ("is thinking", phi);
}
t_bool	is_phi_die(t_philo *phi)
{
	if (gettime () - phi->time_last_eat >= phi->time_die && phi->n_eated == 0)
	{
		//printf ("die time : %zu\n", phi->time_die);
		msg ("died", phi);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_over(t_philo *phis)
{
	int	i;

	i = 0;
	while (i < phis->n_philo)
	{
		if (is_phi_die(&phis[i]))
		{
			*phis[i].isdie = TRUE;
			return (TRUE);
		}
		i ++;
	}
	return (FALSE);
}

t_bool	is_all_eat(t_philo *phis)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (phis->n_must_eat == -1)
		return (FALSE);
	while (i < phis->n_philo)
	{
		if (phis[i].n_eated >= phis->n_must_eat)
			num ++;
		i ++;
	}
	if (num == phis->n_philo)
	{
		*phis->isdie = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor(void *philos)
{
	t_philo	*phis;

	//printf ("monitor\n");
	phis = (t_philo *)philos;
	while (1)
	{
		if (is_over (phis) || is_all_eat (phis))
			break ;
	}
	return (philos);
}
void	*rotine(void *philo)
{
	t_philo	*phi;

	//printf ("rotine\n");
	phi = (t_philo *)philo;
	if (phi->id % 2 == 0)
		ft_sleep (1);
	while (*phi->isdie == FALSE)
	{
		eat (phi);
		slp (phi);
		thk (phi);
	}
	return (philo);
}
void	thread_creat(t_pro *proj)
{
	pthread_t	sudo;
	int			i;

	if (pthread_create (&sudo, NULL, monitor, proj->phis) != 0)
		str_msg ("Error!\n");
	i = 0;
	while (i < proj->phis->n_philo)
	{
		if (pthread_create (&proj->phis[i].thread, NULL, rotine, &proj->phis[i]) != 0)
			str_msg ("Error!\n");
		i ++;
	}
	i = 0;
	if (pthread_join(sudo, NULL) != 0)
		str_msg ("Error!\n");
	while (i < proj->phis->n_philo)
	{
		if (pthread_join(proj->phis[i].thread, NULL) != 0)
			str_msg ("Error!\n");
		i++;
	}
}


int	main(int arc, char **argv)
{
	t_pro	project;
	t_philo	philos[MAX_PHILO];
	t_lock	forks[MAX_PHILO];

	if (arc != 5 && arc != 6)
		return (1);
	if (!is_ok (arc, argv))
		return (1);
	init_prj (&project, philos);
	init_forks (forks, ft_atoi (argv[1]));
	init_phis (&project, forks, argv);
	thread_creat (&project);
	return (0);
}
