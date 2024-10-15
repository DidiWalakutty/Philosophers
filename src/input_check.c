/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 17:24:13 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/15 17:24:13 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*check_input(const char *str)
{
	int			digit_count;
	const char	*valid_num;

	digit_count = 0;
	valid_num = str;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (print_error("This is a negative number"));
	if (!is_digit(*str))
		return (print_error("This is not a number"));
	valid_num = str;
	while (is_digit(*str++))
		++digit_count;
	if (digit_count > 10)
		return (print_error("This number is bigger than INT_MAX"));
	return (valid_num);
}

long	ft_atol(char *str)
{
	long		num;
	const char 	*new_str;

	num = 0;
	new_str = check_input(str);
	if (!new_str)
		return (-1);
	while (is_digit(*new_str))
		num = (num * 10) + (*new_str++ - '0');
	if (num > INT_MAX)
		return ((printf(RED "Error: Number is > than INT_MAX\n" RST)), -1);
	return (num);
}
