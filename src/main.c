/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 16:20:15 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/21 18:26:59 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc <= 5 && argc >= 6)
	{
		printf("Wrong amount of arguments\n");
		return (0);
	}
	if ((argument_check(argc - 1, argv)) == false)
		return (1);
	table = set_table(argc, argv, table);
	if (!table)
		return (1);
	return (0);
}
