/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 16:36:24 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/18 16:47:24 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	set_mutexes(t_table *table)
{
	if (synchronization_mutex(table) != 0)
		return (1)
}