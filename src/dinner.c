/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/23 21:20:02 by diwalaku      ########   odam.nl         */
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
	wait_for_all_philos(philo->table);
}

// Creates threads for each philo and sets time of start simulation.
// Also notifies all philos in meditation_cycle that all threads are ready.
// All med_cycles run simultaneously to this function.
//
//
// probably want to just return and let the main do the cleaning.
// maybe send an int error from the main to begin_feast??
void	begin_feast(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_of_philos == 1)
		dinner_for_one(); // TODO
	else
	{
		while (i < table->num_of_philos)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, meditation_cycle, \
							&table->philos[i]) != 0)
			{
				// delete, free and end program. May need to join before we can destroy???
				// just return and do it there?
				return ;
			}
			i++;
		}
		table->start_simulation = get_time(MILLISECOND);
		if (table->start_simulation == -1)
		{
			// delete, free the whole thing, or just return and do it there?
			return ;
		}
		set_bool(&table->table_mutex, &table->philos_ready, true);
		i = 0;
		while (i < table->num_of_philos)
			// pthread_join
	}
}
