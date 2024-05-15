/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:56:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/15 14:16:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	ft_strlen(char *str)
{
	int i;

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

