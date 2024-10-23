// These are our structs.

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
	t_fork		*right_fork;
	t_fork		*left_fork;
	pthread_t	thread_id;	// a philo is a thread
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
	bool	philos_ready;		// for synchronization of philos in meditation cycle.
	t_mtx	table_mutex;		// avoid races while reading from table
	t_fork	*forks;				// array to all forks
	t_philo	*philos;			// array to all philos
}	t_table;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code

// We init/malloc everything in the following function.
static int	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return ((free(table), 0));
	if (pthread_mutex_init(&table->table_mutex, NULL != 0))
		return ((free_table(table, 1)), 0);
	table->forks = malloc(sizeof(t_fork) * table->num_of_philos);
	if (!table->forks)
		return ((free_table(table, 2)), 0);
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (free_table(table, 3), 0);
		table->forks[i].fork_id = i;
		i++;
	}
	inform_philos(table);
	return (1);
}

// I don't understand the following:
// - set_bool
// - dinner_simulation
void	begin_feast(t_table *table)
{
	int i;

	i = 0;
	if (table->num_of_philos == 1)
		// handle one philo;
	else
	{
		// create philo threads.
		while (i < table->num_of_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, dinner_simulation, \
							&table->philos[i]) != 0)
				// delete, free and end program. May need to join before we can destroy???
			i++;
		}
		// start simulation
		table->start_simulation = gettime(MILLISECOND);
		// We are going to lock the table_mutex, set the bool philos_ready to true and unlock the mutex.
		// threads are ready
		set_bool(&table->table_mutex, &table->philos_ready, true);
		// wait for everyone
		i = 0;
		while (i < table->num_of_philos)
		{
			pthread_create_join(&table->philos[i].thread_id, NULL, NULL);
			// will check for failure later
			i++;
		}
		// if we reach this line, all philos are full.
	}
}

long	gettime(t_time_code time_code)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofdayfailed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (e_time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong input");
	return (1337);
}

// I really don't understand why we need to wait_all_threads.
// Should it already be ready after creating the threads and gettime?
// I am currently only confused up and including the wait_all_threads.
void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data; // what does this do?
	wait_all_threads(philo->table); // synchronizes
	// set last meal time
	while (!simulation_finished(philo->table))
	{
		// is philo full?
		if (philo->full)
			break ;
	}
}

// Spinlock to synchronize philos start.
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, table->philos_ready))
		;
}

// lock and unlock functions so we don't have to write lock and unlock non stop.
// they are getters and setters

bool	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	simulation_finished(t_table *table)
{
	return(get_bool(table->table_mutex, &table->end_simulation));

}
