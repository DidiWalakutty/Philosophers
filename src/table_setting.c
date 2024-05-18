/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 18:08:03 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/18 14:46:59 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		table->philos[i]->meal_check = true;
	}
	else
	{
		table->philos[i]->limited_dinner = false;
		table->philos[i]->meal_check = false;
		table->philos[i]->number_of_meals = 0;
	}
}

int	allocate_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo *) * (table->num_of_philos));
	if (!table->philos)
	{
		printf("Malloc failure!\n");
		return (1);
	}
	while (i <= table->num_of_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
		{
			free_philos(i, table);
			return (1);
		}
		inform_philos(i, table);
		i++;
	}
	return (0);
}

static int	initialize_input(int argc, t_table *table, char **argv)
{
	table->num_of_philos = ft_atol(argv[1]);
	if (table->num_of_philos == 0 || table->num_of_philos > 200)
	{
		printf("Philos should be a minimum of 1 and maximum of 200.\n");
		return (1);
	}
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->limited_dinner = false;
	if (table->time_to_die == 0 || table->time_to_eat == 0 || \
		table->time_to_sleep == 0)
	{
		printf("One or more arguments are 0.\n");
		return (1);
	}
	if (argc == 6)
	{
		table->number_of_meals = ft_atol(argv[5]);
		table->limited_dinner = true;
	}
	return (0);
}

t_table	*set_table(int argc, char **argv, t_table *table)
{
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (initialize_input(argc, table, argv) != 0)
	{
		free(table);
		return (NULL);
	}
	if (allocate_philos(table) != 0)
		return (NULL);
	return (table);
}
