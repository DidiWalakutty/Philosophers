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

// We should make sure we only destroy amount of 
// allocated philos. If we have 5, but only 2 allocated before fail
// we can't destroy the others.
void	clean_table(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = table->philos + 1;
		pthread_mutex_destroy(&philo->monitor_mutex);
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}

void	print_error_message(int error)
{
	if (error == 1)
		printf(RED "Couldn't create pthread\n" RST);
	else if (error == 2)
		printf(RED "Couldn't create monitor_death thread\n" RST);
	else if (error == 3)
		printf(RED "Gettime failed\n" RST);
	else if (error == 4)
		printf(RED "Couldn't join pthreads\n" RST);
}

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

void	join_threads(t_table *table, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_join(table->philos[j].thread_id);
		j++;
	}
}
