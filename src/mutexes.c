/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 16:36:24 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/23 18:48:18 by diwalaku      ########   odam.nl         */
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
			destroy_sync_mutex(table, table->num_of_philos, table->num_of_philos);
			destroy_fork_mutex(table, i);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < table->num_of_philos - 1) // -1 for neighbor on the left.
	{
		table->philos[i]->l_fork = &table->philos[i + 1]->philo_fork;
		i++;
	}
	if (i == 0)
		return (1);
	table->philos[i]->l_fork = &table->philos[0]->philo_fork;
	// // Check if forks are connected correctly to their neighbor
	// for (int i = 0; i < table->num_of_philos; i++) 
	// {
    //     printf("Philosopher %ld: philo_fork address = %p, l_fork address = %p\n",
    //            table->philos[i]->id, (void *)&table->philos[i]->philo_fork,
    //            (void *)table->philos[i]->l_fork);
	// }
	return (1);
}

// Create the synchronization mutexes for each philo and destroys them if not successfull.
static int	sync_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->philos[i]->status_sync_mutex, NULL) != 0)
		{
			destroy_sync_mutex(table, i, -1);
			return (0);
		}
		if (pthread_mutex_init(&table->philos[i]->time_sync_mutex, NULL) != 0)
		{
			destroy_sync_mutex(table, -1, i);
			return (0);
		}
		i++;
	}
	return (1);
}

// Set a sync mutex for status/activities and time for each philosopher.
int	set_mutexes_and_forks(t_table *table)
{
	if (!sync_mutexes(table))
		return (0);
	if (!place_forks(table))
		return (0);
	return (1);
}