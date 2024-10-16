// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   input_check.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/10/15 17:24:13 by diwalaku      #+#    #+#                 */
// /*   Updated: 2024/10/15 17:24:13 by diwalaku      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	check_validity(char *str)
{
	int	i;
	int	digit_count;

	i = 0;
	digit_count = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (error_bool("You're argument contains a negative number"));
	if (!is_digit(str[i]))
		return (error_bool("This iput contains a non-digit"));
	while (is_digit(str[i]))
	{
		digit_count++;
		i++;
	}
	if (digit_count > 10)
		return (error_bool("This number is bigger than INT_MAX"));
	return (true);
}

bool	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_bool("Error: Incorrect number of arguments"));
	while (argv[i])
	{
		if (check_validity(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);	
}

static const char	*update_position(const char *str)
{
	const char	*valid_num;

	valid_num = str;
	while ()
}

long	ft_atol(const char *str)
{
	long		num;
	const char	*new_str;

	num = 0;
	new_str = update_position(str);
	while (is_digit(*new_str))
		num = (num * 10) + (*new_str++ - '0');
	if (num > INT_MAX)
		return ((printf(RED "Error: Number is > than INT_MAX\n" RST)), -1);
	return (num);
}
