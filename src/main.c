/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 16:20:15 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/03 18:08:10 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5)
		exit_error("Wrong amount of arguments");
	if ((argument_check(argc, argv)) == false)
		return (1);
	table = set_table(argv);
	
}
