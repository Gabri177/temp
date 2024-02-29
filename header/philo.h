/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:54 by yugao             #+#    #+#             */
/*   Updated: 2024/02/28 21:40:39 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define MAX_PHILO 200

typedef int				t_bool;
typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_lock;

typedef struct s_philo
{
	int			n_philo;
	int			id;
	t_bool		*isdie;
	pthread_t	thread;
	t_bool		iseating;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_slp;
	int			n_must_eat;
	int			n_eated;
	size_t		time_begin;
	size_t		time_last_eat;
	t_lock		*l_lfork;
	t_lock		*l_rfork;
	t_lock		*l_wrt;
	t_lock		*l_eat;
	t_lock		*l_die;
}						t_philo;

typedef struct s_pro
{
	t_philo	*phis;
	t_bool	is_die;
	t_lock	wrt_lock;
	t_lock	die_lock;
	t_lock	eat_lock;
}						t_pro;
//----------str.c---------------
void	str_errmsg(const char *msg);
//void	str_msg(const char *msg);
void	msg(char *str, t_philo *phi);
//----------utls.c--------------
size_t	gettime(void);
void	ft_sleep(size_t m_time);
int		ft_atoi(char *str);
//----------thread.c------------
void	thread_creat(t_pro *proj);
//----------init.c--------------
t_bool	init_prj(t_pro *pro, t_philo *philos);
t_bool	init_forks(t_lock *forks, int num);
void	init_phis(t_pro *pro, t_lock *fork, char **argv);
//----------action.c------------
void	*rotine(void *philo);
t_bool	destory_all(t_pro *project, char *msg, t_bool retn_val);
t_bool	check_dead(t_philo *phi);
#endif