/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:47:44 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:47:44 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Clamps a value between 0.0 and 1.0
 *
 * Used for color component validation
 *
 * @param value Value to be clamped
 * @return Clamped value between 0.0 and 1.0
 */
double	clamp(double value)
{
	if (value < 0.0)
		return (0.0);
	if (value > 1.0)
		return (1.0);
	return (value);
}

/**
 * @brief Converts RGB values (0.0-1.0) to integer color format
 *
 * Returns 24-bit RGB color in 0xRRGGBB format
 *
 * @param r Red component (0.0-1.0)
 * @param g Green component (0.0-1.0)
 * @param b Blue component (0.0-1.0)
 * @return 24-bit RGB color as unsigned int
 */
unsigned int	rgb_to_int(double r, double g, double b)
{
	int	r_int;
	int	g_int;
	int	b_int;

	r_int = (int)(clamp(r) * 255.0);
	g_int = (int)(clamp(g) * 255.0);
	b_int = (int)(clamp(b) * 255.0);
	return ((r_int << 16) | (g_int << 8) | b_int);
}

/**
 * @brief Cosine-based color palette generator
 *
 * Creates smooth gradients using cosine functions
 *
 * @param t Normalized parameter (0.0-1.0) for color position
 * @param mode Palette mode selector for phase offset
 * @return RGB color value as unsigned int
 */
unsigned int	cosine_palette(double t, int mode)
{
	double	phase;
	double	r;
	double	g;
	double	b;

	phase = mode * 0.3;
	r = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase));
	g = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase + 1.0 / 3.0));
	b = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase + 2.0 / 3.0));
	return (rgb_to_int(r, g, b));
}

/**
 * @brief Psychedelic color palette with high contrast
 *
 * Creates vibrant, oscillating colors
 *
 * @param t Normalized parameter (0.0-1.0) for color position
 * @return RGB color value as unsigned int
 */
unsigned int	psychedelic_palette(double t)
{
	double	r;
	double	g;
	double	b;

	r = 0.5 + 0.5 * sin(16.0 * M_PI * t);
	g = 0.5 + 0.5 * sin(16.0 * M_PI * t + 2.0);
	b = 0.5 + 0.5 * sin(16.0 * M_PI * t + 4.0);
	return (rgb_to_int(r, g, b));
}

/**
 * @brief Applies intensity scaling to base color components
 *
 * Modulates color brightness based on iteration depth
 *
 * @param base_color Base RGB color as unsigned int
 * @param intensity Intensity scaling factor (0.0-1.0)
 * @return Intensity-modulated RGB color as unsigned int
 */
unsigned int	apply_intensity_scaling(unsigned int base_color,
		double intensity)
{
	int	red_component;
	int	green_component;
	int	blue_component;

	red_component = ((base_color >> 16) & 0xFF) * intensity;
	green_component = ((base_color >> 8) & 0xFF) * intensity;
	blue_component = (base_color & 0xFF) * intensity;
	return ((red_component << 16) | (green_component << 8) | blue_component);
}
