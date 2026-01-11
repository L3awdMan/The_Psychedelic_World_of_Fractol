/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:43:16 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:43:16 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Generates final color for fractal pixel based on iteration data
 *
 * Combines smooth iteration values with palette selection
 * Returns RGB color value for display
 *
 * @param smooth_iter Smooth iteration count from fractal calculation
 * @param max_it Maximum iterations for normalization
 * @param palette_mode Color palette selection mode
 * @return RGB color value as unsigned int
 */

unsigned int	generate_fractal_color(double smooth_iter, int max_it,
		int palette_mode)
{
	double			normalized_iter;
	double			color_intensity;
	unsigned int	base_color;

	if (smooth_iter >= (double)max_it)
		return (0x000000);
	normalized_iter = smooth_iter / (double)max_it;
	color_intensity = 1.0 - exp(-0.030 * smooth_iter);
	if (palette_mode == 7)
		return (psychedelic_palette(normalized_iter));
	base_color = cosine_palette(normalized_iter, palette_mode);
	return (apply_intensity_scaling(base_color, color_intensity));
}
