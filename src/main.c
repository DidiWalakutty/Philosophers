/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 21:43:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/04 21:21:42 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Where to run 1 philo?
int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (printf("Wrong amount of arguments\n"), 0);
	if ((argument_check(argc, argv)) == false)
		return (0);
	table = set_table(argc, argv);
	// if (!table)
	// {
	// 	printf("Unable to set the table\n");
	// 	return (0);
	// }
	// start simulation: create threads and join them. 
	// if (!begin_feast(table))
	// 	return (0);
	return (1);
}
