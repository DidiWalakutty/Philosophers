/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 20:52:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 19:10:07 by diwalaku      ########   odam.nl         */
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
			print_debug_activity(TAKEN_FIRST_FORK, philo);
			pthread_mutex_lock(&philo->second_fork->fork);
			print_debug_activity(TAKEN_SEC_FORK, philo);
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
