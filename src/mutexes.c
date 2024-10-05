/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 16:36:24 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/05 19:54:16 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initialize mutexes as right/philo's fork.
// Set reference to left/neighbor's fork.
// Check if there's only 1 philo
static int	place_forks(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->philos[i]->philo_fork, NULL) != 0)
		{
			destroy_mutex_type(table, STATUS, table->num_of_philos);
			destroy_mutex_type(table, TIME, table->num_of_philos);
			destroy_mutex_type(table, FORKS, i);
			return (0);
		}
		i++;
	}
	i = 0;
	// -1 for neighbor on the left.
	while (i < table->num_of_philos - 1)
	{
		table->philos[i]->l_fork = &table->philos[i + 1]->philo_fork;
		i++;
	}
	if (i == 0)
		return (1);
	table->philos[i]->l_fork = &table->philos[0]->philo_fork;
	return (1);
}

// Create the synchronization mutexes for each philo and 
// destroys them if not successfull.
static int	sync_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->philos[i]->status_mutex, NULL) != 0)
		{
			destroy_mutex_type(table, STATUS, i);
			return (0);
		}
		if (pthread_mutex_init(&table->philos[i]->time_mutex, NULL) != 0)
		{
			destroy_mutex_type(table, TIME, i);
			return (0);
		}
		i++;
	}
	return (1);
}

// Set a sync mutex for status/activities and time for each philosopher.
// Also a print_lock.
int	set_mutexes_and_forks(t_table *table)
{
	if (!sync_mutexes(table))
		return (0);
	if (!place_forks(table))
		return (0);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		destroy_mutex_type(table, STATUS, table->num_of_philos);
		destroy_mutex_type(table, TIME, table->num_of_philos);
		return (0);
	}
	return (1);
}
