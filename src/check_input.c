/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:52 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 13:17:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
1. Check if all inputs is a positive number
2. Check if all the others with time is > 60
*/

int	check_input(char **av)
{
	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) <= 0
			|| is_number(av[1]))
		printf("Invalid number of philosopher");
	else if (ft_atoi(av[2]) <= 60 || is_number(av[2]))
		printf("Invalid time to die\n");
	else if (ft_atoi(av[3]) <= 60 || is_number(av[3]))
		printf("Invalid time to eat");
	else if (ft_atoi(av[4]) <= 60 || is_number(av[4]))
		printf("Invalid time to sleep");
	else if (av[5] && (ft_atoi(av[5]) < 0 || is_number(av[5])))
		printf("Invalid no of meals");
	else
		return (0);
	return (1);
}

/**
Frees all the mutexes and malloc arrays
*/
int	end_simulation(char *message, t_table *dining_table,
			t_mtx *forks)
{
	int	i;
	int	n;

	i = 0;
	n = dining_table->num_of_philo;
	if (message != NULL)
		printf("%s\n", message);
	pthread_mutex_destroy(&dining_table->write_lock);
	pthread_mutex_destroy(&dining_table->dead_lock);
	pthread_mutex_destroy(&dining_table->meal_lock);
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (0);
}
