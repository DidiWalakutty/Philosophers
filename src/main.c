/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:01:37 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:01:37 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		*error;
	t_table	table;

	error = 0;
	if (check_input(argc, argv) == false)
		return (1);
	if (set_table(&table, argv) == false)
		return (1);
	// 3 - start dinner simulation
	begin_feast(&table, error);
	if (error > 0)
		print_error_message(error);
	clean_table(table);
	// 4 - clean -> when philos are full or a philo died
}

// TODO:
//
// The input the user gives are milliseconds.
// 2) are we going to set MIN_SEC to 60? and do we do it in microsec or milisec? 
// 3) where are we going to put the philo that takes the fork first???