/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/01 00:49:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int ac, char **av)
{
	t_table		dining_table;
	t_philo		*philos;
	t_mtx		*forks;
	int			num_of_philo;

	if (ac == 5 || ac == 6)
	{
		check_input(av);
		num_of_philo = ft_atoi(av[1]);
		philos = malloc(sizeof(t_philo) * num_of_philo);
		forks = malloc(sizeof(t_mtx) * num_of_philo);
		if (!philos || !forks)
			return (1);
		init_simulation(&dining_table, philos, forks);
		create_threads(&dining_table, philos, forks);
		start_simulation(&dining_table, philos, forks);
		end_simulation(NULL, &dining_table, philos, forks);
	}
	else
		error_exit("Incorrect Input ./philo time_to_die time_to_eat
			time_to_eat [num_of_meals]")
	return (0);
}

citi 142.8
20
