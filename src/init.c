/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/02 16:12:07 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_table(t_table *dining_table)
{
	pthread_mutex_init(&dining_table->write_lock, NULL);
	pthread_mutex_init(&dining_table->dead_lock, NULL);
	pthread_mutex_init(&dining_table->meal_lock, NULL);
}

void	init_philos(t_table *dining_table, t_philo *philos, t_mtx *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].is_eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].write_lock = &dining_table->write_lock;
		philos[i].dead_lock = &dining_table->dead_lock;
		philos[i].meal_lock = &dining_table->meal_lock;
		philos[i].num_of_philo = ft_atoi(av[1]);
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		philos[i].is_dead = 0;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[ft_atoi(av[1])- 1];
		else
			philos[i].right_fork = &forks[i - 1];
		if (av[5])
			philos[i].num_of_times_each_philo_must_eat = ft_atoi(av[5]);
		else
			philos[i].num_of_times_each_philo_must_eat = -1;
		i++;
	}
}

void	init_forks(t_mtx *forks, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_simulation(t_table *table, t_philo *philos, t_mtx *forks, char **av)
{
	int	num_of_philo;

	num_of_philo = philos[0].num_of_philo;
	init_table(table);
	init_forks(forks, num_of_philo);
	init_philos(table, philos, forks, av);
}
