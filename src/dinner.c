/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 20:00:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	dinner_for_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_all_philos(philo->table);
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));
	increase_active_threads(&philo->table->table_mutex, \
				&philo->table->active_threads);
	print_debug_activity(TAKEN_FIRST_FORK, philo);
	while (!dinner_finished(philo->table))
		usleep(200);
	return (NULL);
}

// This function manages the eating process for a philosopher.
// It locks/takes both forks, logs the actions, updates meal time 
// and count, sleeps for the eating duration, and unlocks/drops
// the forks after handling possible meal limit.
static void	eat(t_philo *philo)
{
	toggle_lock_and_fork(LOCK, EATING, philo);
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));
	philo->eaten_meals++;
	print_debug_activity(EATING, philo);
	hyper_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limited_dinner == true && \
		philo->table->num_limit_meals == philo->eaten_meals)
		update_bool(&philo->monitor_mutex, &philo->full, true);
	toggle_lock(UNLOCK, EATING, philo);
}

// We have no given time_to_think.
static void	think(t_philo *philo)
{
	print_debug_activity(THINKING, philo);
}

// wait all philos, start simulation
// endless loop philos
void	*meditation_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_all_philos(philo->table);
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));

	// set last mealtime
	// everytime we pass wait_for_all_philos(), we increaes the num of threads that are running.
	increase_active_threads(&philo->table->table_mutex, \
							&philo->table->active_threads);
	// sync with monitoring function
	// set and increase running_threads_num.
	// set last meal time
	while (!dinner_finished(philo->table))
	{
		// is philo full?
		if (philo->full) // TODO: thread safety
			break ;
		eat(philo);
		print_debug_activity(SLEEPING, philo);
		hyper_sleep(philo->table->time_to_sleep, philo->table);

		think(philo);
	}
	return (NULL);
}

// Creates threads for each philo and sets time of start simulation.
// Also notifies all philos in meditation_cycle that all threads are ready.
// All med_cycles run simultaneously to this function.
//
//
// probably want to just return and let the main do the cleaning.
// maybe send an int error from the main to begin_feast??
int	begin_feast(t_table *table, int *error)
{
	int	i;

	i = -1;
	if (table->num_of_philos == 1)
		if (pthread_create(&table->philos[0].thread_id, NULL, dinner_for_one, \
						&table->philos[0]) != 0)
			return (1);
	else
	{
		while (++i < table->num_of_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, \
								meditation_cycle, &table->philos[i]) != 0)
			{
				// if fails, error message and clean up to i's amount of philos/threads
				// return ;
				return (1);
			}
		}
		// create onderstaand pthread_create in main??
		if (pthread_create(&table->death, NULL, monitoring_death, table) != 0)
			return (2);
		table->start_simulation = get_time(MILLISECOND);
		if (table->start_simulation == -1)
			return (3);
		update_bool(&table->table_mutex, &table->philos_ready, true);
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (pthread_join(table->philos[i].thread_id, NULL))
				return (4);
		}
		// if we reach this line, all philos are full.
		update_bool(&table->table_mutex, &table->end_simulation, true);
		if (pthread_join(&table->table_mutex, NULL));
			return (4);
	}
	return (0);
}
