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

static t_bool	is_over(t_philo *phis)
{
	int	i;

	i = 0;
	while (i < phis->n_philo)
	{
		if (gettime () - phis[i].time_last_eat >= phis[i].time_die)
		{
			msg ("died", &phis[i]);
			pthread_mutex_lock (phis[i].l_die);
			*phis[i].isdie = TRUE;
			pthread_mutex_unlock (phis[i].l_die);
			return (TRUE);
		}
		i ++;
	}
	return (FALSE);
}

static t_bool	is_all_eat(t_philo *phis)
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
		pthread_mutex_lock (phis[i].l_die);
		*phis[i].isdie = TRUE;
		pthread_mutex_unlock (phis[i].l_die);
		return (TRUE);
	}
	return (FALSE);
}

static void	*monitor(void *philos)
{
	t_philo	*phis;

	phis = (t_philo *)philos;
	while (1)
	{
		if (is_over (phis) || is_all_eat (phis))
			break ;
	}
	return (philos);
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
