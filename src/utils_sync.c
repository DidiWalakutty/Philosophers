/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_time.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 00:15:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/22 00:15:16 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// function for updating time
///
// The time we receive as input is in miliseconds.
// However, the usleep() wants microseconds, so we need to
// adjust our input to microseconds.
// gettimeofday will set the seconds and microseconds.

// Convert the tv_seconds and tv_microseconds to the requested unit.
long	get_time(t_time unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	if (unit == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (unit == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (-1);
}

// This function makes sure that each philo in its own
// meditation/dinner cycle, waits until the bool
// philos_ready is true. This way all philos start at the same time.
void	wait_for_all_philos(t_table *table)
{
	while (!read_bool(&table->table_mutex, &table->philos_ready))
		;
}
