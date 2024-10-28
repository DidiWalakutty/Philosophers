/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:48:36 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 18:48:36 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*print_error(char *message)
{
	printf(RED "Error: %s\n" RST, message);
	return (NULL);
}

bool	error_bool(char *message)
{
	printf(RED "Error: %s\n" RST, message);
	return (false);
}

void	print_debug_activity(t_status status, t_philo *philo)
{
	long	time_stamp;

	time_stamp = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (status == TAKEN_FIRST_FORK && \
		!dinner_finished(philo->table))
		printf(W"%-6ld"RST" %i has taken their first fork\t\tnum"B"[🍴 %d 🍴]\n"RST, time_stamp, philo->philo_id, philo->first_fork->fork_id);
	else if (status == TAKEN_SEC_FORK && !dinner_finished(philo->table))
		printf(W"%-6ld"RST" %i has taken their second fork\t\tnum"B"[🍴 %d 🍴]\n"RST, time_stamp, philo->philo_id, philo->second_fork->fork_id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf(GR"%-6ld"RST" %i is eating\t\tnum"B"[🍝 %ld 🍝]\n"RST, time_stamp, philo->philo_id, philo->eaten_meals);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf(W"%-6ld"RST" %i is sleeping 😴\n", time_stamp, philo->philo_id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf(W"%-6ld"RST" %i is thinking 🤔\n", time_stamp, philo->philo_id);
	else if (status == DIED)
		printf(RED"%-6ld"RST"💀 %i died💀\n", time_stamp, philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	print_activity(t_status status, t_philo *philo)
{
	long	time_stamp;

	time_stamp = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((status == TAKEN_FIRST_FORK || status == TAKEN_SEC_FORK) && \
		!dinner_finished(philo->table))
		printf(W"%ld"RST" %i has taken a fork\n", time_stamp, philo->philo_id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf(GR"%ld"RST" %i is eating\n", time_stamp, philo->philo_id);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf(W"%ld"RST" %i is sleeping\n", time_stamp, philo->philo_id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf(W"%ld"RST" %i is thinking\n", time_stamp, philo->philo_id);
	else if (status == DIED)
		printf(RED"%ld"RST" %i died\n", time_stamp, philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
