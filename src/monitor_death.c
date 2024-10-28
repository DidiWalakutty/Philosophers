/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_death.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:59:57 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 19:53:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Waits for all philo threads to be active
static bool	all_threads_active(t_mtx *mutex, long *threads, long philo_num)
{
	bool	check;

	check = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_num)
		check = true;
	pthread_mutex_unlock(mutex);
	return (check);
}

// Check elapsed time since last meal and time_to_die
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (read_bool(&philo->monitor_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND) - read_long(&philo->monitor_mutex, \
												&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000;

	if (elapsed > time_to_die)
		return (true);
	return (false);
}

// Continuously checks if a philo has died (if elapsed meal time is > time_to_die)
void	*monitoring_death(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_active(&table->table_mutex, &table->active_threads, \
								table->num_of_philos))
		;
	while (!dinner_finished(table))
	{
		i = -1;
		while (++i < table->num_of_philos)
		{
			if (philo_died(table->philos + i) && !dinner_finished(table))
			{
				update_bool(&table->table_mutex, &table->end_simulation, true);
				print_debug_activity(DIED, table->philos + i);
			}
		}

	}
	return (NULL);
}

// monitoring waits until all theads are running anymore.