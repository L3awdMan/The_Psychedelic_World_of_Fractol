/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:47:54 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:47:54 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Maps screen pixel X coordinate to complex plane real component
 *
 * Converts pixel position to mathematical coordinate system
 *
 * @param app Pointer to application structure containing view parameters
 * @param x X pixel coordinate on screen
 * @return Real component in complex plane
 */
double	map_pixel_to_real(t_app *app, int x)
{
	return (app->view.cx + (x - WIDTH / 2.0) * app->view.scale);
}

/**
 * @brief Maps screen pixel Y coordinate to complex plane imaginary component
 *
 * Inverts Y axis since screen coordinates start from top-left
 *
 * @param app Pointer to application structure containing view parameters
 * @param y Y pixel coordinate on screen
 * @return Imaginary component in complex plane
 */
double	map_pixel_to_imaginary(t_app *app, int y)
{
	return (app->view.cy - (y - HEIGHT / 2.0) * app->view.scale);
}

/**
 * @brief Sets individual pixel color in image buffer
 *
 * Uses direct memory access for optimal rendering performance
 *
 * @param img Pointer to image structure
 * @param x X coordinate of pixel
 * @param y Y coordinate of pixel
 * @param color RGB color value as unsigned int
 */
void	set_pixel_color(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel_address;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_address = img->data + (y * img->line_len + x
				* (img->bits_per_pixel / 8));
		*(unsigned int *)pixel_address = color;
	}
}
