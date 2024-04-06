/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/06 22:21:02 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// 1. check if input is correct
// 2. malloc the arrays for philo and forks
// 3. init the philos, forks and table
// 4. Create all the threads for the philos.
// 5. Create a seperate thread to check the death status and meals_eatens
// 6. pthread_join and wait for the thread to run
// 7. if everything is successful, clear the mallocs and make sure no leaks

int	main(int ac, char **av)
{
	t_table		table;
	t_philo		philos[MAX_PHILO];
	t_mtx		forks[MAX_PHILO];

	if (ac == 5 || ac == 6)
	{
		if (!check_input(av))
		{
			init_simulation(&table, philos, forks, av);
			start_simulation(&table, philos, forks);
			end_simulation(NULL, &table, philos, forks);
		}
	}
	else
		error_exit("Incorrect Input ./philo time_to_die time_to_eat "
			"time_to_eat [num_of_meals]");
	return (0);
}
