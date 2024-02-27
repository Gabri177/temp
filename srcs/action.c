/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:57:35 by yugao             #+#    #+#             */
/*   Updated: 2024/02/27 20:57:36 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	eat(t_philo *phi)
{
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

void	*rotine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	if (phi->id % 2 == 0)
		ft_sleep (1);
	while (*phi->isdie == FALSE)
	{
		eat (phi);
		msg ("is sleeping", phi);
		ft_sleep (phi->time_slp);
		msg ("is thinking", phi);
	}
	return (philo);
}

t_bool	destory_all(t_pro *project, char *msg, t_bool retn_val)
{
	int	i;

	i = 0;
	if (!msg || msg)
		(void)msg;
	else
		str_errmsg (msg);
	pthread_mutex_destroy (&project->wrt_lock);
	while (i < project->phis->n_philo)
	{
		pthread_mutex_destroy (project->phis[i].l_lfork);
		i ++;
	}
	return (retn_val);
}
