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

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return ((printf(RED "Error: Incorrect number of arguments\n" RST)), 1);
	// 1 - fill table
	set_table(&table, argv);
	
	// 2 - init data -> malloc it all
	// 3 - start dinner simulation
	// 4 - clean -> when philos are full or a philo died
}
