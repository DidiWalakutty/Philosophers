/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_helper.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/04 21:02:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/04 21:03:01 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

bool	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

