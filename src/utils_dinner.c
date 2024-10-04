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

void	print_message(t_philo *philo, t_activity activity)
{
	long		current_time;
	const char	*type[] = {
	[EAT] = "is eating",
	[FORK] = "has taken a fork",
	[SLEEP] = "is sleeping",
	[THINK] = "is thinking",
	};

	pthread_mutex_lock(&philo->table_struct->print_lock);
	if (check_state(philo) != ALIVE)
	{
		pthread_mutex_unlock(&philo->table_struct->print_lock);
		return ;
	}
	current_time = get_time() - philo->table_struct->start_time;
	printf("%ld %lu %s\n", current_time, philo->id, type[activity]);
	pthread_mutex_unlock(&philo->table_struct->print_lock);
}

// Loops until sleeptime is over.
void	ft_sleep(t_philo *philo, long sleeptime)
{
	long	current_time;
	long	time_since;

	current_time = get_time();
	while (time_since < sleeptime)
	{
		if (check_state(philo) != ALIVE)
			return ;
		usleep(50);
		time_since = get_time() - current_time;
	}
}
