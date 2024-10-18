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
