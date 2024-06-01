/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_and_destroy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:56:38 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 22:51:39 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philos(t_table *table, int num_of_philos)
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

void	destroy_mutex_type(t_table *table, t_mutex_type type, int i)
{
	if (type == STATUS)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&table->philos[i]->status_mutex);
			i--;
		}
	}
	else if (type == TIME)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&table->philos[i]->status_time_mutex);
			i--;
		}
	}
	else if (type == FORK)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&table->philos[i]->philo_fork);
			i--;
		}
	}
}

void	join_and_free_philosophers(t_table *table, int current_id)
{
	int	i;

	i = 0;
	pthread_mutex_lock(table->print_lock);
	while (i <= current_id)
	{
		pthread_mutex_lock(table->philos[i]->status_mutex);
		table->philos[i]->status = DEAD;
		pthread_mutex_unlock(table->philos[i]->status_mutex)
		i++;
	}
	pthread_mutex_unlock(table->print_lock);
	i = 0;
	while (i <= current_id)
	{
		if (pthread_join(table->philos[i]->thread, NULL) != 0)
			printf("Error while joining threads for freeing.\n");
			i++;
	}
	table->num_of_philos--;
	destroy_mutex_type(table, STATUS, i);
	destroy_mutex_type(table, TIME, i);
	destroy_mutex_type(table, FORK, i);
	pthread_mutex_destroy(table->print_lock);
	free_philos(table, table->num_of_philos);
}
