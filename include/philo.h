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
typedef	pthread_t		pthrd_t;
typedef enum e_time		t_time;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum e_status
{
	TAKEN_FIRST_FORK,
	TAKEN_SEC_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_status;

typedef enum e_locker
{
	LOCK,
	UNLOCK,
}	t_locker;

typedef enum e_time
{
	MILLISECOND,
	MICROSECOND,
}	t_time;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			philo_id;
	long		eaten_meals;
	bool		full;
	long		last_meal_time;	// time since last meal. MS, so long
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;		// a philo is a thread
	t_mtx		monitor_mutex;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long	num_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_limit_meals;	// if we have a max number of meals
	bool	limited_dinner;
	long	start_simulation;	// when sim started
	bool	end_simulation;		// when a philo dies or all philos are full
	bool	philos_ready;		// for syncing of philos in meditation cycle.
	t_mtx	table_mutex;		// avoid races while reading from table
	t_mtx	write_mutex;
	pthrd_t	grim_reaper;		// pthread that checks if a philo has died
	t_fork	*forks;				// array to all forks
	t_philo	*philos;			// array to all philos
}	t_table;

/* ************************************************************************** */
/*                             Main Functions                                 */
/* ************************************************************************** */

bool	check_input(int argc, char **argv);
bool	set_table(t_table *table, char **argv);
void	begin_feast(t_table *table);
void	*meditation_cycle(void *data);
long	get_time(t_time unit);
void	hyper_sleep(long micro_sec, t_table *table);
void	toggle_lock(t_locker latch, t_status activity, t_philo *philo);
void	*monitoring_death(void *data);

/* ************************************************************************** */
/*                              Helper Functions                              */
/* ************************************************************************** */

bool	initialize_input(t_table *table, char **argv);
void	wait_for_all_philos(t_table *table);
void	update_bool(t_mtx *mutex, bool *bool_condition, bool new_status);
void	update_long(t_mtx *mutex, long *long_value, long new_value);
bool	read_bool(t_mtx *mutex, bool *bool_condition);
long	read_long(t_mtx *mutex, long *value);
bool	dinner_finished(t_table *table);
void	print_activity(t_status status, t_philo *philo);
void	print_debug_activity(t_status status, t_philo *philo); // remove later

/* ************************************************************************** */
/*                              Other Functions                               */
/* ************************************************************************** */

long	ft_atol(char *str);


/* ************************************************************************** */
/*                               Free and Errors                              */
/* ************************************************************************** */

bool	error_bool(char *message);
char	*print_error(char *message);
void	free_table(t_table *table, int code, int processed);

#endif