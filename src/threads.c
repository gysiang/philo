/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:08:25 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/31 12:09:49 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// checks if the dead flag in philo is triggered
// if philo is dead return 1.

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philosopher_routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	// need to make the even num philo sleep
	if (philo->id % 2 == 0)
		usleep_ms(1);
	if (!check_death(philo))
	{
		eating();
		sleeping();
		thinking();
	}
	return (p);
}

int	create_threads(t_table *table, t_philo *philos, t_mtx *forks)
{
	int	i;
	int	num;

	num = philo[0].num_of_philo;
	i = 0;
	// create an observer thread;
	while (i < num)
	{
		if (pthread_create(philos[i].thread, NULL, &philosopher_routine,
					philos[i]) != 0)
				end_simulation("Thread failed to create", table, forks);
		i++;
	}
}

int	start_simulation(t_table *table, t_philo *philos, t_mtx *forks)
{
	int	i;
	int	num;

	num = philo[0].num_of_philo;
	i = 0;
	while (i < num)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
				end_simulation("Thread failed to create", table, forks);
		i++;
	}
}
