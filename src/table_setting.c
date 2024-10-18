/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:46:49 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:46:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Even/odd fork assignment.
static void	*hand_out_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
	// right fork is their own fork
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[philo_pos];
		philo->left_fork = &forks[(philo_pos + 1) % num_of_philos];
	}
	else
	{
		philo->left_fork = &forks[(philo_pos + 1) % num_of_philos];
		philo->right_fork = &forks[philo_pos];
	}
}

static void	inform_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		hand_out_forks(philo, table->forks, i);
	}
}

static int	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return ((free(table), 0));
	table->forks = malloc(sizeof(t_fork) * table->num_of_philos);
	if (!table->forks)
	{
		free(table->philos);
		free(table);
		return (0);
	}
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (free_forks_and_philos(table, i), 0);
		table->forks[i].fork_id = i;
		i++;
	}
	inform_philos(table);
	return (1);
}

// The time we receive as input is in miliseconds.
// However, the usleep() wants microseconds, so we need to
// adjust our input to microseconds.
bool	set_table(t_table *table, char **argv)
{
	if (initialize_input(table, argv) == false)
		return ((free(table)), false);
	if (!allocate_philos(table))
		return (false);
	return (true);
}
