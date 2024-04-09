/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:08:25 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 14:04:52 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// checks if the dead flag in philo is triggered
// mutex is added because the observer thread can modify it, the lock is to
// prevent this from changing at the point of reading
// if philo is dead return 1.

int	check_death(t_philo *philo)
{
	if (philo->table->dead_flag == 1)
	{
		return (1);
	}
	return (0);
}

void	*philosopher_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep_ms(1);
	while (!check_death(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (p);
}

int	start_simulation(t_table *table, t_philo *philos, t_mtx *forks)
{
	pthread_t	controller;
	int			i;
	int			num;

	num = philos->table->num_of_philo;
	i = 0;
	if (pthread_create(&controller, NULL, &observer_routine, philos) != 0)
		end_simulation("Thread failed to create", table, forks);
	while (i < num)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philosopher_routine,
				&philos[i]) != 0)
			end_simulation("Thread failed to create", table, forks);
		i++;
	}
	i = 0;
	if (pthread_join(controller, NULL) != 0)
		end_simulation("Thread join error", table, forks);
	while (i < num)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			end_simulation("Thread join error", table, forks);
		i++;
	}
	return (0);
}
