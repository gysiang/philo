/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 13:59:38 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_table(t_table *dining_table, char **av)
{
	dining_table->dead_flag = 0;
	dining_table->num_of_philo = ft_atoi(av[1]);
	dining_table->time_to_die = ft_atoi(av[2]);
	dining_table->time_to_eat = ft_atoi(av[3]);
	dining_table->time_to_sleep = ft_atoi(av[4]);
	dining_table->start_time = get_current_time();
	if (av[5])
		dining_table->target_meals = ft_atoi(av[5]);
	else
		dining_table->target_meals = -1;
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
		philos[i].meals_eaten = 0;
		philos[i].is_eating = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % dining_table->num_of_philo];
		philos[i].table = dining_table;
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &dining_table->write_lock;
		philos[i].dead_lock = &dining_table->dead_lock;
		philos[i].meal_lock = &dining_table->meal_lock;
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

void	init_simulation(t_table *table, t_philo *philos,
		t_mtx *forks, char **av)
{
	init_table(table, av);
	init_forks(forks, table->num_of_philo);
	init_philos(table, philos, forks, av);
}
