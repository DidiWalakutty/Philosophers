/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:43:38 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 21:58:37 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Where to run 1 philo?
int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments\n");
		return (0);
	}
	if ((argument_check(argv)) == false)
		return (0);
	table = set_table(argc, argv);
	if (!table)
	{
		printf("Unable to set the table\n");
		return (0);
	}
	// start simulatoin: create threads and join them. 
	if (!begin_feast(table))
		return (0);
	return (1);
}
