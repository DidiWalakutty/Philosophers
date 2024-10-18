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

void	free_forks_and_philos(t_table *table, int count)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < count)
		{
			pthread_mutex_destroy(&table->forks[i].fork);
			i++;
		}
		free(table->forks);
	}
	i = 0;
	if (table->philos)
	{
		while (i < count)
		{
			pthread_mutex_destroy(&table->philos[i].);//what should we destroy?)}
			i++;
		}
		free(table->philos);
	}
	free(table);
}
