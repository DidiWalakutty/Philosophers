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

// Even/odd fork assignment that ensures each philo gets two forks in a
// circular manner, while avoiding deadlock situations.
// It creates an alternating order, which breaks symmetry.
// This function only assigns the forks.
static void	hand_out_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	num_of_philos;

	num_of_philos = philo->table->num_of_philos;
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

// Give each philo it's id and basic information.
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

// Allocate the structs for philos and forks.
// Create a mutex for each philo/fork.
// Inform/set all values for each philo.
static int	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return ((free(table), 0));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return ((free_table(table, 1)), 0);
	table->forks = malloc(sizeof(t_fork) * table->num_of_philos);
	if (!table->forks)
		return ((free_table(table, 2)), 0);
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (free_table(table, 3), 0);
		table->forks[i].fork_id = i;
		i++;
	}
	inform_philos(table);
	return (1);
}

// This function sets everything we need before we
// start the actual simulation.
bool	set_table(t_table *table, char **argv)
{
	if (initialize_input(table, argv) == false)
		return ((free(table)), false);
	if (!allocate_philos(table))
		return (false);
	return (true);
}
