/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:19:12 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:19:12 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Calculates appropriate fractal escape value for given coordinates
 *
 * Routes computation to correct fractal algorithm based on current type
 *
 * @param app Pointer to application structure containing fractal type
 * @param real_coord Real coordinate in complex plane
 * @param imag_coord Imaginary coordinate in complex plane
 * @param max_iterations Maximum iterations before escape
 * @return Smooth iteration count for color calculation
 */
static double	calculate_fractal_escape(const t_app *app, double real_coord,
		double imag_coord, int max_iterations)
{
	if (app->type == FRACT_MANDEL)
		return (mandelbrot(real_coord, imag_coord, max_iterations));
	else if (app->type == FRACT_JULIA)
		return (mister_julia(real_coord, imag_coord, max_iterations, app));
	else if (app->type == FRACT_NEWTON3)
		return (newton_fractal(real_coord, imag_coord, max_iterations));
	else if (app->type == FRACT_MANDEL_FLOWER)
		return (mandel_flower(real_coord, imag_coord, max_iterations));
	else
		return (mandelbrot(real_coord, imag_coord, max_iterations));
}

/**
 * @brief Calculates final color value for individual pixel
 *
 * Integrates coordinate mapping, fractal computation, and color generation
 *
 * @param app Pointer to application structure
 * @param x X pixel coordinate on screen
 * @param y Y pixel coordinate on screen
 * @param max_iterations Maximum iterations for fractal calculation
 * @return RGB color value as unsigned int
 */
unsigned int	render_pixel_color(t_app *app, int x, int y, int max_iterations)
{
	double	real_coordinate;
	double	imaginary_coordinate;
	double	smooth_iteration_count;

	real_coordinate = map_pixel_to_real(app, x);
	imaginary_coordinate = map_pixel_to_imaginary(app, y);
	smooth_iteration_count = calculate_fractal_escape(app, real_coordinate,
			imaginary_coordinate, max_iterations);
	return (generate_fractal_color(smooth_iteration_count, max_iterations,
			app->current_palette));
}

/**
 * @brief Renders complete fractal frame
 *
 * Processes each pixel and applies appropriate coloring
 *
 * @param app Pointer to application structure
 */
void	render_complete_frame(t_app *app)
{
	int	pixel_x;
	int	pixel_y;
	int	max_iterations;

	pixel_y = 0;
	max_iterations = app->view.max_it;
	while (pixel_y < HEIGHT)
	{
		pixel_x = 0;
		while (pixel_x < WIDTH)
		{
			set_pixel_color(&app->img, pixel_x, pixel_y, render_pixel_color(app,
					pixel_x, pixel_y, max_iterations));
			pixel_x++;
		}
		pixel_y++;
	}
}
