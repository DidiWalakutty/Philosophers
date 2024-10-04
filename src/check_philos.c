/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:43:11 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 21:43:11 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_status	check_state(t_philo *philo)
{
	t_status	condition;

	pthread_mutex_lock(&philo->status_mutex);
	condition = philo->status;
	pthread_mutex_unlock(&philo->status_mutex);
	return (condition);
}
