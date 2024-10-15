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

#include "../include/philo.h"

static bool	negative_input(char **argv)
{
	int	i;
	int	value;

	i = 1;
	value = 0;
	while (argv[i])
	{
		value = ft_atol(argv[i]);
		if (value == -1)
			return (true);
		i++;
	}
	return (false);
}

// The time we receive as input is in miliseconds.
// However, the usleep() wants microseconds, so we need to
// adjust our input to microseconds.
bool	set_table(t_table *table, char **argv)
{
	if (negative_input(argv) == true)
		return (false);
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * MICRO_SECONDS;
	table->time_to_eat = ft_atol(argv[3]) * MICRO_SECONDS;
	table->time_to_sleep = ft_atol(argv[4]) * MICRO_SECONDS;
	if (table->time_to_die < MIN_SEC || table->time_to_eat < MIN_SEC || \
		table->time_to_sleep < MIN_SEC)
		return ((printf("Use timestamps bigger than 60 ms\n")), false);
	if (argv[5])
	{
		table->num_limit_meals = ft_atol(argv[5]);
		// do we want to add a bool:
		// - limited_dinner = true?
	}
	else
		table->num_limit_meals = -1;
}
