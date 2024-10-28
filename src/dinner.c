/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 18:00:36 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function manages the eating process for a philosopher.
// It locks/takes both forks, logs the actions, updates meal time 
// and count, sleeps for the eating duration, and unlocks/drops
// the forks after handling possible meal limit.
static void	eat(t_philo *philo)
{
	toggle_lock(LOCK, EATING, philo);
	print_debug_activity(TAKEN_FIRST_FORK, philo);
	print_debug_activity(TAKEN_SEC_FORK, philo);
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
	// set last meal time
	while (!dinner_finished(philo->table))
	{
		// is philo full?
		if (philo->full) // TODO: thread safety
			break ;
		eat(philo);
		print_debug_activity(SLEEPING, philo);
		hyper_sleep(philo->table->time_to_sleep, philo->table);
		
		// sleep -> write_status and precise usleep
		
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
void	begin_feast(t_table *table)
{
	int	i;

	i = 0;
	// if (table->num_of_philos == 1)
	// 	dinner_for_one(); // TODO
	// else
	// {
		while (i < table->num_of_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, \
								meditation_cycle, &table->philos[i]) != 0)
			{
				printf("Couldn't create philo %i's thread\n");
				// delete, free and end program. May need to join before we can destroy???
				// just return and do it there?
				return ;
			}
			i++;
		}
		if (pthread_create(&table->grim_reaper, NULL, monitoring_death, table) != 0)
		{
			printf("Couldn't create monitor_death thread\n");
			return ;
		}
		// put start_sim and set_bool in a different function?
		table->start_simulation = get_time(MILLISECOND);
		if (table->start_simulation == -1)
		{
			printf("Gettime failed\n");
			// delete, free the whole thing, or just return and do it there?
			return ;
		}
		update_bool(&table->table_mutex, &table->philos_ready, true);
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (pthread_join(table->philos[i].thread_id, NULL))
				return ;
		}
		// if we reach this line, all philos are full.
	// }
}
