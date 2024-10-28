/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_death.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:59:57 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/28 18:03:25 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_threads_

// 
void	*monitoring_death(void *data)
{
	t_table *table;

	table = (t_table *)data;
	while (!all_)
	return (NULL);
}

// monitoring waits until all theads aren't running anymore.