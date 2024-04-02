/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:14:47 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/30 15:08:49 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
1. checks if num of philo is 1, if 1, philo does not eat and sleeps till die
2. tries to take up left fork and right fork
3. when both forks are taken up, start eating
4. modify meals eaten and last meal time
5. release both forks

*/

void	eating(t_philo *philo)
{
	if (philo->num_of_philo == 1)
		return (usleep_ms(philo->time_to_die));
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	philo->eating = 1;
	usleep_ms(philo->time_to_eat);
	philo->eating = 0;
	philo->meals_eaten += 1;
	philo->last_meal = get_current_time();
	pthread_mutex_lock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	usleep_ms(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}