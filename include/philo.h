/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo2.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:15:27 by anonymous     #+#    #+#                 */
/*   Updated: 2024/10/14 20:15:27 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <stdbool.h>	// booleans
# include <pthread.h>	// thread and mutex
# include <sys/time.h>	// gettimeofday
# include <limits.h>	// int min and max
# include <string.h>	// memset
// printf zelf protecten met eigen mutex lock!!!
// printf kan niet garanderen dat een andere thread eerder print
// dan dat een andere thread zijn printf aanroept.
// exit_error is verboden

typedef pthread_mutex_t	t_mtx;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;


typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;	// time since last meal. MS, so long
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;	// a philo is a thread
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;	// if we have a max number of meals
	long	start_simulation;	// when sim started
	bool	end_simulation;		// when a philo dies or all philos are full
	t_fork	*forks;				// array to all forks
	t_philo	*philos;			// array to all philos

}	t_table;