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

static bool	validate_table_values(t_table *table)
{
	if (table->philo_nbr == -1 || table->time_to_die == -1 || \
		table->time_to_eat == -1 || table->time_to_sleep == -1)
		return (error_bool("Number is > than INT_MAX\n"));
	if (table->limited_dinner == true && table->num_limit_meals == -1)
		return (error_bool("Number is > than INT_MAX\n"));
	else if (table->time_to_die < MIN_SEC || table->time_to_eat < MIN_SEC || \
		table->time_to_sleep < MIN_SEC)
		return (error_bool("Use timestamps bigger than 60 ms\n"));
	return (true);
}

// The time we receive as input is in miliseconds.
// However, the usleep() wants microseconds, so we need to
// adjust our input to microseconds.
bool	set_table(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * MICRO_SECONDS;
	table->time_to_eat = ft_atol(argv[3]) * MICRO_SECONDS;
	table->time_to_sleep = ft_atol(argv[4]) * MICRO_SECONDS;
	table->limited_dinner = false;
	table->num_limit_meals = -1;
	if (argv[5])
	{
		table->num_limit_meals = ft_atol(argv[5]);
		table->limited_dinner = true;
	}
	//	do we need to free the t_table struct no validated values? Not allocated yet...
	if (validate_table_values(table) = false)
		return (false);
	return (true);
}
