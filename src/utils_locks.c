/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 20:52:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/11/05 21:20:16 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function either locks or unlocks both forks.
void	toggle_lock_and_fork(t_locker latch, t_status activity, t_philo *philo)
{
	if (activity == EATING)
	{
		if (latch == LOCK)
		{
			pthread_mutex_lock(&philo->first_fork->fork);
			print_activity(TAKEN_FIRST_FORK, philo);
			pthread_mutex_lock(&philo->second_fork->fork);
			print_activity(TAKEN_SEC_FORK, philo);
		}
		else if (latch == UNLOCK)
		{
			pthread_mutex_unlock(&philo->first_fork->fork);
			pthread_mutex_unlock(&philo->second_fork->fork);
		}
	}
}

// Increases the number of threads running.
void	increase_active_threads(t_mtx *mutex, long *philo_threads)
{
	pthread_mutex_lock(mutex);
	(*philo_threads)++;
	pthread_mutex_unlock(mutex);
}

int	join_philosophers_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (1);
	}
	update_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->death, NULL);
	return (0);
}

static void	*dinner_for_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_all_philos(philo->table);
	update_long(&philo->monitor_mutex, &philo->last_meal_time, \
				get_time(MILLISECOND));
	increase_active_threads(&philo->table->table_mutex, \
				&philo->table->active_threads);
	print_activity(TAKEN_FIRST_FORK, philo);
	while (!dinner_finished(philo->table))
		usleep(200);
	return (NULL);
}

int	meal_for_one(t_table *table)
{
	if (pthread_create(&table->philos[0].thread_id, NULL, dinner_for_one, \
						&table->philos[0]) != 0)
		return (1);
	return (0);
}
