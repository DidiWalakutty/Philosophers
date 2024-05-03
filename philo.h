/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 16:10:01 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/05/03 18:03:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// printf zelf protecten met eigen mutex lock!!!
# include <string.h>	// memset
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <stdio.h>		// printf
# include <sys/time.h>	// gettimeofday
# include <fcntl.h>		// macro to open files (O_CREAT, O_WRONLY, O_RDONLY)
# include <pthread.h>	// thread and mutex
# include <stdbool.h>	// booleans
# include <stdint.h>	// cross-compilers

typedef struct s_time
{

}	t_data;

typedef struct s_philo
{
}	t_philo;

typedef struct s_table
{
}	t_table;

// Functions

// Utils 
void	exit_error(char *str);
int		ft_strlen(char *str);
bool	is_digit(int num);

// Checks
bool	argument_check(int argc, char **argv);

// Initalize
t_table	*set_table(char **argv);

#endif