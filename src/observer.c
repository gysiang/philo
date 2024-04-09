/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 14:23:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * if philo is eating , the meal_lock mutex (also shared by eating) will make
 * this function wait until it can lock it.
*/
static int	starved(t_philo *philo, uint32_t time_to_die)
{
	int	is_starved;

	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->is_eating == 0)
		is_starved = 1;
	else
		is_starved = 0;
	pthread_mutex_unlock(philo->meal_lock);
	return (is_starved);
}

int	death_checker(t_philo *philos)
{
	int		i;
	int		n;
	t_table	*table;

	i = 0;
	n = philos->table->num_of_philo;
	table = philos->table;
	while (i < n)
	{
		if (starved(&philos[i], philos[i].table->time_to_die))
		{
			pthread_mutex_lock(philos->dead_lock);
			print_philo_action(DIED, philos, philos[i].id);
			table->dead_flag = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// check if all the philo has hit the target meals
int	all_philo_ate(t_philo *philos)
{
	int	i;
	int	target_meals;
	int	met_target;
	int	num;

	i = 0;
	num = philos->table->num_of_philo;
	target_meals = philos->table->target_meals;
	met_target = 0;
	if (target_meals == -1)
		return (0);
	while (i < num)
	{
		if (philos[i].meals_eaten >= target_meals)
			met_target++;
		i++;
	}
	if (met_target == num)
	{
		pthread_mutex_lock(philos->dead_lock);
		philos->table->dead_flag = 1;
		pthread_mutex_unlock(philos->dead_lock);
	}
	return (0);
}

void	*observer_routine(void *p)
{
	t_philo	*philos;

	philos = (t_philo *)p;
	while (1)
	{
		if (death_checker(philos) || all_philo_ate(philos))
		{
			break ;
		}
	}
	return (p);
}
