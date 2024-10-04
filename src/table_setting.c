/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 18:08:03 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/04 21:23:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// We set the basics for every philosopher and give each its ID.
// Not sure if I need the variable meal_check
static void	inform_philos(int i, t_table *table)
{
	table->philos[i]->id = i + 1;
	table->philos[i]->time_to_die = table->time_to_die;
	table->philos[i]->time_to_eat = table->time_to_eat;
	table->philos[i]->time_to_sleep = table->time_to_sleep;
	table->philos[i]->status = ALIVE;
	table->philos[i]->table_struct = table;
	if (table->limited_dinner == true)
	{
		table->philos[i]->limited_dinner = true;
		table->philos[i]->number_of_meals = table->number_of_meals;
	}
	else
	{
		table->philos[i]->limited_dinner = false;
		table->philos[i]->number_of_meals = 0;
	}
}

// Allocate memory for table->philos and each philosopher in it.
int	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo *) * (table->num_of_philos));
	if (!table->philos)
	{
		printf("Malloc failure!\n");
		free(table);
		return (0);
	}
	while (i < table->num_of_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
		{
			free_philos(table, i);
			return (0);
		}
		inform_philos(i, table);
		i++;
	}
	return (1);
}

// Check and set all argv's in our table struct.
static int	initialize_input(int argc, char **argv, t_table *table)
{
	table->num_of_philos = ft_atol(argv[1]);
	if (table->num_of_philos == 0 || table->num_of_philos > MAX_PHILOS)
		return (printf("Philos should be a min of 1 and max of 200.\n"), 0);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if ((table->time_to_die < 60) || (table->time_to_sleep < 60))
		return (printf("Time_to_die and/or time_to_sleep is too short.\n"), 0);
	table->limited_dinner = false;
	if (table->time_to_die == 0 || table->time_to_eat == 0 || \
		table->time_to_sleep == 0)
		return (printf("One or more arguments are 0.\n"), 0);
	if (argc == 6)
	{
		table->number_of_meals = ft_atol(argv[5]);
		table->limited_dinner = true;
	}
	return (1);
}

// Preparing the table by initalizing the input and allocate 
// the philos, mutexes and forks.
t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (!initialize_input(argc, argv, table))
		return (NULL);
	if (!allocate_philos(table))
		return (NULL);
	if (!set_mutexes_and_forks(table))
	{
		free_philos(table, table->num_of_philos - 1);
		return (NULL);
	}
	table->start_time = get_time();
	return (table);
}
