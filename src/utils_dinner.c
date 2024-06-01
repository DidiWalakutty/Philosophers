/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:44:03 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 21:44:03 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_dinner.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 13:29:58 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/01 18:59:00 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Calculates the time in milliseconds since the epoch.
// tv_sec converts seconds to milliseconds by doing * 1000.
// tv_usec converts microseconds to milliseconds from microsec by doing / 1000.
long	get_time(void)
{
	struct timeval	start_time;
	long			time_ms;

	gettimeofday(&start_time, NULL);
	time_ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (time_ms);
}

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
}