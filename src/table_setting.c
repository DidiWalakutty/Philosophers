/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table_setting.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 20:38:28 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/03 17:57:13 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	input_validation(t_table *table, char **argv)
{
	int	i;

	i = 0;
	// In which struct do we set the number of philos, time to eat, die and sleep??? 
}

t_table	*set_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (input_validation(&table, argv))
		// set numbers into arguments 
}
