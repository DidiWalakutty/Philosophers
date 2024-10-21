/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/22 01:11:37 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// wait all philos, start simulation
// endless loop philos
//

void	*meditation_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table); // TODO:
	

	return (NULL);
}

void	begin_feast(t_table *table)
{
	int i;

	i = 0;
	if (table->num_of_philos == 1)
		// handle one philo;
	else
	{
		// create philo threads.
		while (i < table->num_of_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, meditation_cycle, \
							&table->philos[i]) != 0)
				// delete, free and end program. May need to join before we can destroy???
			i++;
		}
		// threads are ready
	}
}