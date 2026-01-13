/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:19:42 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:19:42 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Parses decimal part of floating point number
 *
 * @param str String containing decimal digits
 * @param i Pointer to current position in string (modified)
 * @return Decimal part as double value
 */
double	parse_decimal_part(const char *str, int *i)
{
	double	decimal_value;
	double	fraction;

	decimal_value = 0.0;
	fraction = 0.1;
	while (str[*i])
	{
		decimal_value += (str[*i] - '0') * fraction;
		fraction *= 0.1;
		(*i)++;
	}
	return (decimal_value);
}

/**
 * @brief Simple atof implementation for parsing floating point arguments
 *
 * Converts string to double for Julia parameters
 *
 * @param str String representation of floating point number
 * @return Parsed double value
 */
double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		i;

	result = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		result += parse_decimal_part(str, &i);
	}
	return (result * sign);
}
