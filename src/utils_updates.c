/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_locks_and_updates.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 19:45:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/25 18:46:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// These functions either read or adjust the values of booleans and longs.
// They do this while locking first, doing their action, and unlocking.

// This function updates the bool value.
void	update_bool(t_mtx *mutex, bool *bool_condition, bool new_status)
{
	pthread_mutex_lock(mutex);
	*bool_condition = new_status;
	pthread_mutex_unlock(mutex);
}

// This function updates the long value.
void	update_long(t_mtx *mutex, long *long_value, long new_value)
{
	pthread_mutex_lock(mutex);
	*long_value = new_value;
	pthread_mutex_unlock(mutex);
}

// This function reads and returns the value of the bool.
bool	read_bool(t_mtx *mutex, bool *bool_condition)
{
	bool	read_value;

	pthread_mutex_lock(mutex);
	read_value = *bool_condition;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

// This function reads and returns the value of long.
long	read_long(t_mtx *mutex, long *value)
{
	long	read_value;

	pthread_mutex_lock(mutex);
	read_value = *value;
	pthread_mutex_unlock(mutex);
	return (read_value);
}

// This function check whether or not the simulation is finished.
bool	dinner_finished(t_table *table)
{
	return (read_bool(&table->table_mutex, &table->end_simulation));
}
