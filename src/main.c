/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 16:20:15 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/23 18:45:00 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		return (0);
	return (1);
}
