/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:27:52 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:27:52 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table, int code, int processed)
{
	int	i;

	i = -1;
	if (code >= 1 && table->philos)
	{
		if (code == 5)
		{
			while (++i < processed)
				pthread_mutex_destroy(&table->philos[i].monitor_mutex);
		}
		free(table->philos);
	}
	if (code >= 2)
		pthread_mutex_destroy(&table->table_mutex);
	if (code >= 3)
		pthread_mutex_destroy(&table->write_mutex);
	i = -1;
	if (code >= 4)
	{
		while (++i < processed)
			pthread_mutex_destroy(&table->forks[i].fork);
		free(table->forks);
	}
	free(table);
}
