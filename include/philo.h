/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 16:10:01 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/27 20:31:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// printf zelf protecten met eigen mutex lock!!!
// exit_error is verboden
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// thread and mutex
# include <stdbool.h>	// booleans

typedef enum s_status
{
	ALIVE,
	DEAD,
	FULL
}	t_status;

typedef enum s_activity
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIE
}	t_activity;

typedef struct s_time
{
}	t_data;

typedef struct s_philo
{
	long			id;
	pthread_mutex_t	status_sync_mutex;
	t_status		status;
	pthread_mutex_t	time_sync_mutex;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	struct s_table	*table_struct;
	bool			limited_dinner;
	long			number_of_meals;
	pthread_t		thread;
	pthread_mutex_t	philo_fork;	// or r_fork? It's the philo's fork
	pthread_mutex_t	*l_fork;
	// bool			meal_check; 
}	t_philo;

typedef struct s_table
{
	t_philo		**philos;
	long		num_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_meals;
	long		start_time;
	bool		limited_dinner;
}	t_table;

// Functions
// Utils_1
int		ft_strlen(char *str);
bool	is_digit(int num);

// Utils_2
void	free_philos(int i, t_table *table);
void	destroy_sync_mutex(t_table *table, int status, int mutex);
void	destroy_fork_mutex(t_table *table, int i);
// Checks
bool	argument_check(char **argv);
long	ft_atol(char *str);

// Initalize
t_table	*set_table(int argc, char **argv);
int		allocate_philos(t_table *table);
int		set_mutexes_and_forks(t_table *table);
long	get_time(void);

#endif