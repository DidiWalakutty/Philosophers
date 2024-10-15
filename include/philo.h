/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:01:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:01:50 by diwalaku      ########   odam.nl         */
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

// Can we use INT_MAX?
// Converting miliseconds to microseconds by * 1000
// We want a minimum time_to of 60 miliseconds, so 60 * 1000.
# define INT_MAX 2147483647
# define MICRO_SECONDS 1000
# define MIN_SEC 60000

/* ************************************************************************** */
/*                                ANSI Colors                                 */
/* ************************************************************************** */
// Usage:  printf(RED "This is bold red text!" RST "\n");

#define RST "\033[0m"      // Reset
#define RED "\033[1;31m"   // Bold Red
#define GR  "\033[1;32m"   // Bold Green
#define Y   "\033[1;33m"   // Bold Yellow
#define B   "\033[1;34m"   // Bold Blue
#define M   "\033[1;35m"   // Bold Magenta
#define C   "\033[1;36m"   // Bold Cyan
#define W   "\033[1;37m"   // Bold White


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
	long	num_limit_meals;	// if we have a max number of meals
	long	start_simulation;	// when sim started
	bool	end_simulation;		// when a philo dies or all philos are full
	t_fork	*forks;				// array to all forks
	t_philo	*philos;			// array to all philos

}	t_table;

/* ************************************************************************** */
/*                                  Functions                                 */
/* ************************************************************************** */

bool	set_table(t_table *table, char **argv);


/* ************************************************************************** */
/*                              Helper Functions                              */
/* ************************************************************************** */

const char	*print_error(const char *message);
long		ft_atol(char *str);

#endif