/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/05 15:47:37 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_table(t_table *dining_table)
{
	dining_table->dead_flag = 0;
	pthread_mutex_init(&dining_table->write_lock, NULL);
	pthread_mutex_init(&dining_table->dead_lock, NULL);
	pthread_mutex_init(&dining_table->meal_lock, NULL);
}

static void	enter_input_to_philo(t_philo *philos, char **av)
{
	philos->num_of_philo = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		philos->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
	}
	else
		philos->num_of_times_each_philo_must_eat = -1;
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
		enter_input_to_philo(&philos[i], av);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &dining_table->write_lock;
		philos[i].dead_lock = &dining_table->dead_lock;
		philos[i].meal_lock = &dining_table->meal_lock;
		philos[i].is_dead = &dining_table->dead_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[ft_atoi(av[1])- 1];
		else
			philos[i].right_fork = &forks[i - 1];
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
	init_table(table);
	init_philos(table, philos, forks, av);
}
