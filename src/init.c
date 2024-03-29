/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/29 23:20:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_table(t_table *dining_table)
{
	table->clear_table = 0;
	//table->philos = philos;
	pthread_mutex_init(&dining_table->write_lock, NULL);
	pthread_mutex_init(&dining_table->dead_lock, NULL);
	pthread_mutex_init(&dining_table->meal_lock, NULL);
}

t_philo	init_philo(t_philo *philos, t_mtx *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
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
			philos[i].right_fork = &forks[philos[i].num_of_philo - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
	return (philos);
}

// init the forks for each philo
t_mtx	init_forks(t_mtx *forks, int num_of_philo)
{
	int	i;

	forks = malloc(ft_atoi(av[1]) * sizeof(t_mtx));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
