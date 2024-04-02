/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:13 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	starved_to_death(t_philo *philo, uint32_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
			&& philo->is_eating == 0)
	{
		pthread_mutex_lock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_lock(philo->meal_lock);
	return (0);
}

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
		if (starved_to_death(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos[i].dead_lock);
			print_message("died", &philos[i], philos->id);
			philos[i].is_dead = 1;
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
			met_target++;
		i++;
	}
	if (philos[0].num_of_philo == met_target)
		return (1);
	return (0);
}

/**
This routine will keep checking if the is_dead flag
*/
void	*observer_routine(void *p)
{
	t_philo *philos;

	philos = (t_philo *)p;
	printf("%s", "observer routine started\n");
	while (1)
	{
		if (monitor_for_death(philos) || check_if_all_ate(philos))
			break;
	}
	return (p);
}
