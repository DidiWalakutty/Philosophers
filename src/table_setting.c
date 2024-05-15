/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 18:08:03 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/15 17:57:50 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	initialize_input(t_table *table, char **argv)
{
	int	i;

	i = 1;
	table->num_of_philos = ft_atol(argv[1]);
	if (table->num_of_philos == 0 || table->num_of_philos > 200)
	{
		printf("Philos should be a minimum of 1 and maximum of 200.\n");
		return (1);
	}
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_die == 0 || table->time_to_eat == 0 || \
		table->time_to_sleep == 0)
	{
		printf("One or more arguments are 0.\n");
		return (1);
	}
	// table->time_started = get_time_ms();
	return (0);	
}

t_table	*set_table(char **argv, t_table *table)
{
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (initialize_input(table, argv) != 0)
	{
		free(table);
		return (NULL);		
	}
	return (table);
}
