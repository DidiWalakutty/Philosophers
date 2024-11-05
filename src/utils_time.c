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
	{
		printf("Failed retrieving gettimeofday\n");
		return (-1);
	}
	if (unit == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (unit == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
	{
		printf("Gettimeofday failed\n");
		return (-1);
	}
}

// This function makes sure that each philo in its own
// meditation/dinner cycle, waits until the bool
// philos_ready is true. This way all philos start at the same time.
void	wait_for_all_philos(t_table *table)
{
	while (!read_bool(&table->table_mutex, &table->philos_ready))
		;
}

// A precise usleep that uses a combination of usleep (> 1 millisec)
// and a spinlock for precise timing that also checks if the sim ended.
// Checks if the elapsed time has reached the given sleep duration.
void	hyper_sleep(long micro_sec, t_table *table)
{
	long	start;
	long	passed_time;
	long	sleep_left;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < micro_sec)
	{
		if (dinner_finished(table))
			break ;
		passed_time = get_time(MICROSECOND) - start;
		sleep_left = micro_sec - passed_time;
		if (sleep_left > 1000)
		{
			usleep(sleep_left / 2);
			if (dinner_finished(table))
				break ;
		}
		else
		{
			while (get_time(MICROSECOND) - start < micro_sec)
				;
		}
	}
}

// monitoring waits until all theads are running anymore.

// re_sync philos for thinking time.
// Even num_of_philos and its id is even, we let them
// hyper_sleep for a very small amount of time for balance.
// Else we trigger a thinking phase before the simulation.
// This helps spread out the philos' actions.
void	resync_thinking(t_philo *philo)
{
	if (philo->table->num_of_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			hyper_sleep(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2)
			think(philo, true);
	}
}
