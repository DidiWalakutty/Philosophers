/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_free_and_destroy.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:56:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/28 13:43:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philos(int num_of_philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table);
}

void	destroy_sync_mutex(t_table *table, int status, int mutex)
{
	while (status >= 0)
	{
		pthread_mutex_destroy(&table->philos[status]->status_sync_mutex);
		status--;
	}
	while (mutex >= 0)
	{
		pthread_mutex_destroy(&table->philos[mutex]->time_sync_mutex);
		mutex--;
	}
}

void	destroy_fork_mutex(t_table *table, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&table->philos[i]->philo_fork);
		i--;
	}
}
