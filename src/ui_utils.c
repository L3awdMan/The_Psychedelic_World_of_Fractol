/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:18:46 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:18:46 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Appends a string to buffer at position i
 *
 * @param dst Destination buffer
 * @param i Starting position in buffer
 * @param buf_size Size of destination buffer
 * @param s Source string to append
 * @return New position after appending
 */
int	append_str(char *dst, int i, int buf_size, const char *s)
{
	while (*s)
	{
		if (i + 1 < buf_size)
			dst[i] = *s;
		i++;
		s++;
	}
	return (i);
}

/**
 * @brief Appends a positive integer to buffer at position i
 *
 * @param dst Destination buffer
 * @param i Starting position in buffer
 * @param buf_size Size of destination buffer
 * @param value Integer value to append
 * @return New position after appending
 */
int	append_int(char *dst, int i, int buf_size, int value)
{
	char	tmp[11];
	int		len;

	if (value == 0)
	{
		if (i + 1 < buf_size)
			dst[i] = '0';
		return (i + 1);
	}
	len = 0;
	while (value > 0 && len < 11)
	{
		tmp[len] = (char)('0' + (value % 10));
		len++;
		value /= 10;
	}
	while (len--)
	{
		if (i + 1 < buf_size)
			dst[i] = tmp[len];
		i++;
	}
	return (i);
}

/**
 * @brief Formats zoom level with proper precision
 *
 * @param buf Buffer to store formatted zoom string
 * @param buf_size Size of buffer
 * @param zoom Zoom level value
 */
void	format_zoom(char *buf, int buf_size, double zoom)
{
	int	i;

	if (buf_size <= 0)
		return ;
	if (zoom <= 0.0)
		zoom = 1.0;
	i = 0;
	i = append_str(buf, i, buf_size, "Zoom x");
	if (zoom < 10000.0)
		i = append_int(buf, i, buf_size, (int)(zoom + 0.5));
	else
		i = append_int(buf, i, buf_size, (int)(zoom + 0.5));
	if (i < buf_size)
		buf[i] = '\0';
	else if (buf_size > 0)
		buf[buf_size - 1] = '\0';
}

/**
 * @brief Returns fractal name for display
 *
 * @param type Fractal type enumeration
 * @return String containing fractal name
 */
char	*get_fractal_name(t_type type)
{
	if (type == FRACT_MANDEL)
		return ("Mandelbrot");
	else if (type == FRACT_JULIA)
		return ("Julia Set");
	else if (type == FRACT_NEWTON3)
		return ("Newton z^3");
	else if (type == FRACT_MANDEL_FLOWER)
		return ("Mandel Flower");
	else
		return ("Unknown");
}
