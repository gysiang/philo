/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:55 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/30 01:09:42 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av)
{
	t_table		dining_table;
	t_philo		*philos;
	t_mtx		*forks;
	int			num_of_philo;

	if (ac == 5 || ac == 6)
	{
		// check the input
		if (!check_input(av))
		{
			num_of_philo = ft_atoi(av[1]);
			philos = malloc(sizeof(t_philo) * num_of_philo);
			if (!philos)
				return (1);
			init_table(&dining_table);
			// init the philos array
			init_philos(philos, forks, av)
			// init the forks
			init_forks(forks, num_of_philo);
			// make the threads
			// free everthing
		}
	}
	else
		error_exit("Incorrect Input ./philo time_to_die time_to_eat
			time_to_eat [num_of_meals]")
	return (0);
}
