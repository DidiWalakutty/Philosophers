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

// 	// i = 0;
	// if (table->philos[i])
	// {
	// 	while (i < count)
	// 	{
	// 		pthread_mutex_destroy(&table->philos[i].);//what should we destroy?)}
	// 		i++;
	// 	}
	// 	free(table->philos);
	// }
//

// void	free_allocation_forks(t_table *table, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		pthread_mutex_destroy(&table->forks[i].fork);
// 		i++;
// 	}
// 	free(table->forks);
// 	free(table->philos);
// 	pthread_mutex_destroy(&table->table_mutex);
// 	free(table);
// }

void	free_table(t_table *table, int code)
{
	int	i;

	i = 0;
	if (code >= 1)
		free(table->philos);
	if (code >= 2)
		pthread_mutex_destroy(&table->table_mutex);
	if (code == 3)
	{
		while (i < table->num_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i].fork);
			i++;
		}
		free(table->forks);
	}
	free(table);
}
