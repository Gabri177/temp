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

static t_bool	check_argv(int arc, char **argv)
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

static t_bool	check_argv_num(int arc, char **argv)
{
	int	i;

	i = 1;
	while (i < arc)
	{
		if (ft_atoi (argv[i]) <= 0)
			return (FALSE);
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
	if (!check_argv (arc, argv) || !check_argv_num (arc, argv))
		return (str_errmsg ("Please check the argument!\n"), 1);
	if (!init_prj (&project, philos))
		return (str_errmsg ("Init proj error!\n"), 1);
	if (!init_forks (forks, ft_atoi (argv[1])))
		return (str_errmsg ("Init forks error!\n"), 1);
	init_phis (&project, forks, argv);
	thread_creat (&project);
	destory_all (&project, NULL, FALSE);
	return (0);
}
