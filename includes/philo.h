/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:25:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/09 14:28:02 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/select.h>

# define MAX_PHILO 300
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef pthread_mutex_t	t_mtx;

typedef struct s_table
{
	int			dead_flag;
	int			num_of_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			target_meals;
	size_t		start_time;
	t_mtx		write_lock;
	t_mtx		dead_lock;
	t_mtx		meal_lock;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals_eaten;
	int				is_eating;
	size_t			last_meal;
	struct s_table	*table;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
	t_mtx			*write_lock;
	t_mtx			*dead_lock;
	t_mtx			*meal_lock;
}	t_philo;

// utils
int		is_number(const char *s);
int		ft_atoi(const char *str);
int		check_input(char **av);
void	print_philo_action(char *message, t_philo *philo, int id);
void	usleep_ms(size_t milliseconds);
size_t	get_current_time(void);

// init
void	init_table(t_table *dining_table, char **av);
void	init_forks(t_mtx *forks, int num_of_philo);
void	init_philos(t_table *dining_table, t_philo *philos, t_mtx *forks,
			char **av);

// routines
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*philosopher_routine(void *p);
void	*observer_routine(void *p);
int		check_death(t_philo *philo);
int		all_philo_ate(t_philo *philos);
int		death_checker(t_philo *philos);

// simulation
void	init_simulation(t_table *table, t_philo *philos, t_mtx *forks,
			char **av);
int		start_simulation(t_table *table, t_philo *philos, t_mtx *forks);
int		end_simulation(char *message, t_table *dining_table, t_mtx *forks);

#endif
