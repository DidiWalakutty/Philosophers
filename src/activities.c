/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:28:16 by diwalaku          #+#    #+#             */
/*   Updated: 2024/06/01 23:28:16 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	dinner_for_one(t_philo *philo)
{
	print_message(philo, FORK);
	ft_sleep(philo, philo->time_to_die);
	print_message(philo, DIE);
}

void	set_latest_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
}