/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:49:32 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:49:32 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Calculates smooth iteration count for anti-aliasing
 *
 * Uses logarithmic smoothing to eliminate banding artifacts
 * Returns fractional iteration count for smooth color gradients
 *
 * @param z_re Real part of complex number z
 * @param z_im Imaginary part of complex number z
 * @param iter Current iteration count
 * @return Smooth iteration count as double
 */
double	calculate_smooth_iteration(double z_re, double z_im, int iter)
{
	double	log_magnitude;
	double	smoothed_value;

	log_magnitude = log(z_re * z_re + z_im * z_im) / 2.0;
	smoothed_value = log(log_magnitude / log(2.0)) / log(2.0);
	return (iter + 1 - smoothed_value);
}

/**
 * @brief Calculates Mandelbrot set escape iterations
 *
 * Formula: z = z^2 + c, where z starts at origin (0,0)
 * Returns smooth iteration count when point escapes to infinity
 *
 * @param c_re Real part of complex constant c
 * @param c_im Imaginary part of complex constant c
 * @param max_iter Maximum iterations before considering point as in set
 * @return Smooth iteration count or max_iter if point is in set
 */
double	mandelbrot(double c_re, double c_im, int max_iter)
{
	double	z_re;
	double	z_im;
	double	z_re_squared;
	double	z_im_squared;
	int		iter;

	z_re = 0.0;
	z_im = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		z_re_squared = z_re * z_re;
		z_im_squared = z_im * z_im;
		if (z_re_squared + z_im_squared > 4.0)
			return (calculate_smooth_iteration(z_re, z_im, iter));
		z_im = 2.0 * z_re * z_im + c_im;
		z_re = z_re_squared - z_im_squared + c_re;
		iter++;
	}
	return (max_iter);
}

/**
 * @brief Calculates Julia set escape iterations
 *
 * Formula: z = z^2 + c, where z starts at pixel coordinates
 * Uses constant c parameter from Julia set configuration
 *
 * @param z_re Real part of starting complex number z
 * @param z_im Imaginary part of starting complex number z
 * @param max_iter Maximum iterations before considering point as in set
 * @param app Pointer to application structure containing Julia parameters
 * @return Smooth iteration count or max_iter if point is in set
 */
double	mister_julia(double z_re, double z_im, int max_iter, const t_app *app)
{
	double	z_re_squared;
	double	z_im_squared;
	double	temp_real;
	int		iter;

	iter = 0;
	while (iter < max_iter)
	{
		z_re_squared = z_re * z_re;
		z_im_squared = z_im * z_im;
		if (z_re_squared + z_im_squared > 4.0)
			return (calculate_smooth_iteration(z_re, z_im, iter));
		temp_real = z_re_squared - z_im_squared + app->julia_real;
		z_im = 2.0 * z_re * z_im + app->julia_imag;
		z_re = temp_real;
		iter++;
	}
	return (max_iter);
}
