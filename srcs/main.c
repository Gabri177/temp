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

t_bool	check_argv(int arc, char **argv)
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

int	main(int arc, char **argv)
{
	t_pro	project;
	t_philo	philos[MAX_PHILO];
	t_lock	forks[MAX_PHILO];

	if (arc != 5 && arc != 6)
		return (1);
	if (!check_argv (arc, argv))
		return (1);
	init_prj (&project, philos);
	init_forks (forks, ft_atoi (argv[1]));
	init_phis (&project, forks, argv);
	thread_creat (&project);
	destory_all (&project, NULL);
	return (0);
}
