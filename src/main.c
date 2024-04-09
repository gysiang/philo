/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 13:09:25 by gyong-si         ###   ########.fr       */
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
		if (check_input(av) == 1)
		{
			return (1);
		}
		init_simulation(&table, philos, forks, av);
		start_simulation(&table, philos, forks);
		end_simulation(NULL, &table, forks);
	}
	return (0);
}
