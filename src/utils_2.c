/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:56:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/15 17:52:14 by diwalaku      ########   odam.nl         */
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

// int	print_error(char *str)
// {
// 	write(2, str, ft_strlen(str));
// 	return (1);
// }

bool	is_digit(int num)
{
	if (num >= '0' && num <= '9')
		return (true);
	else
		return (false);
}
