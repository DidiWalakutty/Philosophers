/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:43:29 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 22:09:32 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// In this cycle the philo will keep on doing
// the eat, sleep, thinking untill it's either
// FULL or DEAD.
void	*meditation_cycle(void *param)
{
	t_philo	*this_philo;

	this_philo = (t_philo *) param;
	if (this_philo->id % 2 != 0)
		usleep((this_philo->time_to_die / 4) * 1000);
	while (check_state(this_philo) == ALIVE)
	{
		eating(this_philo);
		sleeping(this_philo);
		print_message(this_philo, THINK);
		if (this_philo->table_struct->num_of_philos % 2 != 0)
			usleep(this_philo->time_to_die / 4);
	}
	return (NULL)	
}


// Set a function for 1 philo?
//
// Name for cycle:
	// sith_meditation_cycle
	// sith_ritual_cycle
	// elven_wisdom_ritual
	// elven_reflection_cycle.
int	begin_feast(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_of_philos == 1)
	{
		dinner_for_one();
		return (1);
	}
	table->start_time = get_time();
	while (i < table->num_of_philos)
	{
		set_last_meal(table->philos);
		if (pthread_create(&table->philos[i]->thread, NULL, \
							&meditation_cycle, table->philos[i]) != 0)
		{
			printf("Couldn't create thread for philo: %ld.\n", table->philos[i]);
			join_and_free_philosophers(table, i);
			return (0);
		}
	}
	return (1);
}
