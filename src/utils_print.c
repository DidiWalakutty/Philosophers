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

#include "../include/philo.h"

const char	*print_error(const char *message)
{
	printf(RED "Error: %s\n" RST, message);
	return (NULL);
}