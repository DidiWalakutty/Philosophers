/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:47:32 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/04/20 21:03:55 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Checks for length of each argv, if it's digits only and the min/max length
bool	validation_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (ft_strlen(argv[i]) == 0)
		{
			printf("Argv[%i] is empty\n", i);
			return (false);
		}
		while (argv[i][j])
		{
			if (is_digit(argv[i][j]) == false)
			{
				printf("Argv[%i]-[%i] is not a digit\n", i, j);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static int	check_numbers(t_table *table, char **argv)
{
	int i = 0;
	// In which struct do we set the number of philos, time to eat, die and sleep??? 
}