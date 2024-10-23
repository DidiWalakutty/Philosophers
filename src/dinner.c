/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 17:26:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/23 20:49:02 by diwalaku      ########   odam.nl         */
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
				return ;
			}
			i++;
		}
		if ((table->start_simulation = get_time()) == -1)
		{
			printf("Failed retrieving gettimeofday\n");
			return ;
		}
			// delete, free the whole thing
		set_bool(&table->table_mutex, &table->philos_ready, true);
	}
}
