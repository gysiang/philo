/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/01 00:59:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// check all the philo
// if the current time is greater than time to die set is_dead=1
int	monitor_for_death(t_philo *philos)
{
	int	i;
	int	n;

	i = 0;
	n = philos[0].num_of_philo;
	while (i < n)
	{
		if (get_current_time() - philos[i].last_meal >= philos[i].time_to_die
				&& philos[i].eating == 0)
		{
			pthread_mutex_lock(philos[i].dead_lock);
			print_message("died", &philos[i], philos.id);
			philos[i].is_dead == 1
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// check if all the philo has hit the target meals
int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int target_meals;
	int	met_target;

	i = 0;
	target_meals = philos[0].num_of_times_each_philo_must_eat;
	met_target = 0;
	if (target_meals == -1)
		return (0);
	while (i < philos[0].num_of_philo)
	{
		if (philos[i].meals_eaten >= philos[i].num_of_times_each_philo_must_eat)
		{
			met_target++;
		}
		i++;
	}
	if (philos[0].num_of_philo == target_meals)
		return (1);
	return (0);
}

/**
This routine will keep checking if the is_dead flag
*/
void	*observer_routine(void *p)
{
	t_philo *philos;
	int	condition;

	condition = 0;
	philos = (t_philo *)p;
	while (!condition)
	{
		if (monitor_for_death(philos) || check_if_all_ate(philos))
			break;
	}
	return (p);
}
