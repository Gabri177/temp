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

int	main(int arc, char **argv)
{
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (arc != 5 && arc != 6)
		return (1);
	if (!is_ok (arc, argv))
		return (1);
	//t_creat_philo (arc, argv, philos);
	return (0);
}
