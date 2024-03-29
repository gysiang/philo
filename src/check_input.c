/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:52 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/28 16:28:18 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
1. Check if all inputs is a positive number
2. Check if all the others with time is > 60
*/

int	check_input(char **av)
{
	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) <= 0
			|| is_number(av[1]))
		error_exit("Invalid number of philosopher");
	if (ft_atoi(av[2]) <= 60 || is_number(av[2]))
		error_exit("Invalid time to die");
	if (ft_atoi(av[3]) <= 60 || is_number(av[3]))
		error_exit("Invalid time to eat");
	if (ft_atoi(av[4]) <= 60 || is_number(av[4]))
		error_exit("Invalid time to sleep");
	if (av[5] && ft_atoi(av[5]) || is_number(av[5]))
		error_exit("Invalid no of meals");
	return (0);
}
