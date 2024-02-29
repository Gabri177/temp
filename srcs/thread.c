/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:05:04 by yugao             #+#    #+#             */
/*   Updated: 2024/02/28 22:39:15 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static t_bool	is_phi_die(t_philo *phi)
{
	pthread_mutex_lock (phi->l_eat);
	if ((gettime () - phi->time_last_eat >= phi->time_die) && phi->iseating == FALSE)
		return (pthread_mutex_unlock (phi->l_eat), TRUE);
	pthread_mutex_unlock (phi->l_eat);
	return (FALSE);
}

static t_bool	is_over(t_philo *phis)
{
	int	i;

	i = 0;
	while (i < phis->n_philo)
	{
		if (is_phi_die(&phis[i]))
		{
			msg ("died", phis);
			pthread_mutex_lock (phis->l_die);
			*phis[i].isdie = TRUE;
			pthread_mutex_unlock (phis->l_die);
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
	while (i < phis[0].n_philo)
	{
		pthread_mutex_lock (phis[i].l_eat);
		if (phis[i].n_eated >= phis[i].n_must_eat)
			num ++;
		pthread_mutex_unlock (phis[i].l_eat);
		i ++;
	}
	if (num == phis[0].n_philo)
	{
		pthread_mutex_lock (phis[0].l_die);
		*phis->isdie = TRUE;
		pthread_mutex_unlock (phis[0].l_die);
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
		if (is_over (phis) == TRUE || is_all_eat (phis) == TRUE)
			break ;
	}
	return (philos);
}

void	thread_creat(t_pro *proj)
{
	pthread_t	sudo;
	int			i;

	if (pthread_create (&sudo, NULL, monitor, proj->phis) != 0)
			destory_all (proj, "Error!\n: Thread create!\n", FALSE);
	i = 0;
	while (i < proj->phis->n_philo)
	{
		if (pthread_create (&proj->phis[i].thread, NULL, rotine, &proj->phis[i]) != 0)
			destory_all (proj, "Error!\n: Thread create!\n", FALSE);
		i ++;
	}
	i = 0;
	if (pthread_join(sudo, NULL) != 0)
		destory_all (proj, "Error!\n: Thread join!\n", FALSE);
	while (i < proj->phis->n_philo)
	{
		if (pthread_join(proj->phis[i].thread, NULL) != 0)
			destory_all (proj, "Error!\n: Thread join!\n", FALSE);
		i++;
	}
}
