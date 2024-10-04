/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:47:32 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/04 21:16:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	argument_check(int count, char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (i < count)
	{
		num = ft_atoi(argv[i]);
		if (!num)
			return (false);
		if (num > INT_MAX)
			return ((printf("Argv[%i] is bigger than MAX_INT\n", i), false));
		if (num < 0 || num < INT_MIN)
			return ((printf("Argv[%i] is smaller than 0 or MIN_INT\n", i)), \
					false);
		if (ft_strlen(argv[i]) == 0)
			return (printf("Argv[%i] is empty\n", i), false);
		if (!only_digits(argv[i]))
			return (printf("Argv[%i] contains a non-digit char\n", i), false);
		i++;
	}
	return (true);
}
