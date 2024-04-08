/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:05:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/08 15:29:17 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	starved(t_philo *philo, uint32_t time_to_die)
{
	int	is_starved;

	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die)
		is_starved = 1;
	else
		is_starved = 0;
	pthread_mutex_unlock(philo->meal_lock);
	return (is_starved);
}

int	death_checker(t_philo *philos)
{
	int	i;
	int	n;
	t_table *table;

	i = 0;
	n = philos->table->num_of_philo;
	table = philos->table;
	while (i < n)
	{
		if (starved(&philos[i], philos[i].table->time_to_die))
		{
			//printf("entered into death checker\n");
			pthread_mutex_lock(philos->dead_lock);
			print_philo_action(DIED, philos, philos[i].id);
			table->dead_flag = 1;
			//printf("death checker print: %d\n", table->dead_flag);
			pthread_mutex_unlock(philos->dead_lock);
			//printf("exiting death checker\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// check if all the philo has hit the target meals
int	all_ate(t_philo *philos)
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
	//printf("observer routine started\n");
	while (1)
	{
		//printf("entered into observer loop\n");
		if (death_checker(philos))
		{
			//printf("before observer break");
			break ;
		}
	}
	//printf("observer routine ended");
	return (p);
}
