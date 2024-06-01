
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

typedef enum s_status
{
	ALIVE,	
	DEAD,
	FULL
}	t_status;

typedef enum s_mutex_type
{
	STATUS,
	TIME,
	PRINT,
	FORK,
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
	t_status		status;
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

// Functions
// Utils_1
int		ft_strlen(char *str);
bool	is_digit(int num);

// Utils_2
void	free_philos(t_table *table, int i);
void	join_and_free_philosophers(t_table *table, int current_id);
void	destroy_mutex_type(t_table *table, t_mutex_type type, int i);

// Checks
bool	argument_check(char **argv);
long	ft_atol(char *str);

// Initalize
t_table	*set_table(int argc, char **argv);
int		allocate_philos(t_table *table);
int		set_mutexes_and_forks(t_table *table);
long	get_time(void);

// Dinner
int			begin_feast(t_table *table);
void		set_last_eat(t_philo *philo);
t_status	check_state(t_philo *philo);


// // Check for "place forks" function: if forks are connected correctly to their neighbor
// for (int i = 0; i < table->num_of_philos; i++) 
// {
//     printf("Philosopher %ld: philo_fork address = %p, l_fork address = %p\n",
//            table->philos[i]->id, (void *)&table->philos[i]->philo_fork,
//            (void *)table->philos[i]->l_fork);
// }

#endif