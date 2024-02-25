/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:04:54 by yugao             #+#    #+#             */
/*   Updated: 2024/02/25 16:06:22 by yugao            ###   ########.fr       */
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
typedef struct s_philo
{
	int				n_philo;
	int				id;
	pthread_t		thread;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_slp;
	size_t			n_must_eat;
	size_t			n_eated;
	size_t			time_last_eat;
	pthread_mutex_t	*l_lfork;
	pthread_mutex_t	*l_rfork;
	pthread_mutex_t	*l_eat;
	pthread_mutex_t	*l_slp;
	pthread_mutex_t	*l_prt;
}						t_philo;

//----------str.c---------------
size_t	str_len(const char *str);
void	str_errmsg(const char *msg);
void	str_msg(const char *msg);

//----------utls.c--------------
size_t	gettime(void);
void	ft_sleep(size_t m_time);
int		ft_atoi(char *str);

//----------thread.c------------
t_bool	t_creat_philo(int arc, char **argv, t_philo *phi);
void	*philo_do(void *arg);

#endif