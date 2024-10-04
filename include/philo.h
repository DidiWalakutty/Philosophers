/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/04 21:15:17 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/04 21:15:54 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>	// malloc, free
# include <string.h>	// memset
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// thread and mutex
# include <stdbool.h>	// booleans
// printf zelf protecten met eigen mutex lock!!!
// exit_error is verboden

# define MAX_PHILOS	200
# define INT_MIN	-2147483648
# define INT_MAX	2147483647

typedef enum s_state
{
	ALIVE,	
	DEAD,
	FULL
}	t_state;

typedef enum s_mutex_type
{
	STATUS,
	TIME,
	PRINT,
	FORKS,
}	t_mutex_type;

typedef enum s_activity
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIE
}	t_activity;

typedef struct s_philo
{
	struct s_table	*table_struct;
	t_state			status;
	long			id;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	bool			limited_dinner;
	long			number_of_meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	philo_fork;	// or r_fork? It's the philo's fork
	pthread_mutex_t	*l_fork;
	// bool			meal_check; 
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	print_lock;
	t_philo			**philos;
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_meals;
	long			start_time;
	bool			limited_dinner;
	// pthread_mutex_t mutex_lock; ??
}	t_table;

//-------------------------------------------------------------------------//
//                                  Functions                              //
//-------------------------------------------------------------------------//

t_table	*set_table(int argc, char **argv);
int		begin_feast(t_table *table);
void	dinner_for_one(t_philo *philo);

//-------------------------------------------------------------------------//
//                                  Dinner                                 //
//-------------------------------------------------------------------------//

void	set_last_eat(t_philo *philo);
void	set_latest_meal(t_philo *philo);
t_state	check_state(t_philo *philo);

//-------------------------------------------------------------------------//
//                                    Set                                  //
//-------------------------------------------------------------------------//

int		allocate_philos(t_table *table);
int		set_mutexes_and_forks(t_table *table);
void	destroy_mutex_type(t_table *table, t_mutex_type type, int i);
void	ft_sleep(t_philo *philo, long sleeptime);
long	get_time(void);

//-------------------------------------------------------------------------//
//                                  Helpers                                //
//-------------------------------------------------------------------------//

bool	argument_check(int argc, char **argv);
void	print_message(t_philo *philo, t_activity activity);
int		print_error(char *message);
int		ft_strlen(char *str);
bool	is_digit(int num);
bool	only_digits(char *str);
long	ft_atol(char *str);
int		ft_atoi(const char *str);

//-------------------------------------------------------------------------//
//                               Free and Error                            //
//-------------------------------------------------------------------------//

void	free_philos(t_table *table, int i);
void	join_and_free_philosophers(t_table *table, int current_id);

// // Check for "place forks" function: if forks are 
// 		connected correctly to their neighbor
// for (int i = 0; i < table->num_of_philos; i++) 
// {
//     printf("Philosopher %ld: philo_fork address = %p, l_fork address = %p\n",
//            table->philos[i]->id, (void *)&table->philos[i]->philo_fork,
//            (void *)table->philos[i]->l_fork);
// }

#endif