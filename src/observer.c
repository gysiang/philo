/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/07 00:31:28 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	starved(t_philo *philo, uint32_t time_to_die)
{
	if (get_current_time() - philo->last_meal >= time_to_die
			&& philo->is_eating == 0)
		return (1);
	return (0);
}

int	death_checker(t_philo *philos)
{
	int	i;
	int	n;

	i = 0;
	n = philos->table->num_of_philo;
	while (i < n)
	{
		if (starved(&philos[i], philos[i].table->time_to_die))
		{
			pthread_mutex_lock(philos[i].dead_lock);
			if (!check_death(philos))
			{
				print_philo_action(DIED, philos, philos[i].id);
				*philos[i].is_dead = 1;
			}
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
	int num;

	i = 0;
	num = philos->table->num_of_philo;
	target_meals = philos->table->num_of_philo;
	met_target = 0;
	if (target_meals == -1)
		return (0);
	while (i < num)
	{
		if (philos[i].meals_eaten >= target_meals)
			met_target++;
		i++;
	}
	if (num == met_target)
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
		if (death_checker(philos) || check_if_all_ate(philos))
			break;
	}
	return (p);
}
