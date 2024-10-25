/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 20:52:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/25 22:40:58 by diwalaku      ########   odam.nl         */
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
			pthread_mutex_lock(&philo->right_fork->fork);
			pthread_mutex_lock(&philo->left_fork->fork);
		}
		else if (latch == UNLOCK)
		{
			pthread_mutex_unlock(&philo->right_fork->fork);
			pthread_mutex_unlock(&philo->left_fork->fork);
		}
	}
}
