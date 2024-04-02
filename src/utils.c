/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:29:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/30 12:25:20 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	error_exit(const char *s)
{
	printf("%s\n", s);
	return (1);
}

int	is_number(const char *s)
{
	if (*s == '\0')
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (1);
		s++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

void	print_message(char *message, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!check_death(philo))
		printf("%zu %d %s\n", time, id, message);
	pthread_mutex_unlock(philo->write_lock);
}
