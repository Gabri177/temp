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