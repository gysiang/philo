/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:27:54 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 14:27:18 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	usleep_ms(size_t milliseconds)
{
	size_t	t;

	t = get_current_time();
	while (1)
	{
		if (get_current_time() - t >= milliseconds)
			break ;
		usleep(50);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
