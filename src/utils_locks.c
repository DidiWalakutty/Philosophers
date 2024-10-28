/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 20:52:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 16:34:30 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function either locks or unlocks both forks.
void	toggle_lock(t_locker latch, t_status activity, t_philo *philo)
{
	if (activity == EATING)
	{
		if (latch == LOCK)
		{
			pthread_mutex_lock(&philo->first_fork->fork);
			pthread_mutex_lock(&philo->second_fork->fork);
		}
		else if (latch == UNLOCK)
		{
			pthread_mutex_unlock(&philo->first_fork->fork);
			pthread_mutex_unlock(&philo->second_fork->fork);
		}
	}
}
