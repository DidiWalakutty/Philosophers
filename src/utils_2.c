/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/20 18:56:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/18 13:41:22 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philos(int i, t_table *table)
{
	while (i >= 0)
	{
		free(table->philos[i]);
		i--;
	}
	free(table->philos);
	free(table);
}
