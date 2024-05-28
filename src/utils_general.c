/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:47:32 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/28 14:06:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Need to check for MAX int?
bool	argument_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (ft_strlen(argv[i]) == 0)
		{
			printf("Argv[%i] is empty.\n", i);
			return (false);
		}
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
			{
				printf("Argv[%i][%i] is not a digit\n", i, j);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

long	ft_atol(char *str)
{
	long	i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

bool	is_digit(int num)
{
	if (num >= '0' && num <= '9')
		return (true);
	else
		return (false);
}
