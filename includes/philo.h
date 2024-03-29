/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:25:38 by gyong-si          #+#    #+#             */
/*   Updated: 2024/03/29 23:20:38 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/select.h>

# define MAX_PHILO 200
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef pthread_mutex_t	t_mtx;

/**
	id : tracks the id no of each philo
	meals_counter: for each meal eaten +1
	time_to_die: time taken to die
	time_to_eat: time to eat a meal
	time_to_sleep: time taken to sleep
	start_time: time when program starts
	is_eating: if philo is eating it will be 1
	num_of_philo: no of philo entered by user
	target_meals: no of meals all philo must eat entered by user
	is_dead: if philo is dead it will be 1 else 0
	thread: the philo thread for the philo
	l_fork/r_fork: mutex for editing the l and r forks
	w_lock : mutex for writing text to output
	d_lock: mutex to control to state of philo
	m_lock: mutex to control when philo is eating
*/

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_eaten;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	size_t		last_meal;
	int			is_eating;
	int			num_of_philo;
	int			num_of_times_each_philo_must_eat;
	int			is_dead;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_mtx		*write_lock;
	t_mtx		*die_lock;
	t_mtx		*meal_lock;
}	t_philo;

/**
if	any of the philo is dead, it triggers the dead flag
in program
philos is the array that stores all the philo data
*/
typedef struct s_table
{
	int			clear_table;
	t_mtx		write_lock;
	t_mtx		dead_lock;
	t_mtx		meal_lock;
	//t_philo		*philos;
} t_table;

/**
Utils
*/
int	is_number(const char *s);
int	ft_atoi(const char *str);
int	error_exit(const char *s);
int	check_input(char **av);
void	init_table(t_table *dining_table);
t_mtx	init_forks(t_mtx *forks, int num_of_philo);
t_philo	init_philo(t_philo *philos, t_mtx *forks, char **av);

#endif
