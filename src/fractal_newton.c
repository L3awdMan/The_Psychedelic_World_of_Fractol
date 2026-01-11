/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_newton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:49:10 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:49:10 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * Calculates Newton fractal for equation z^3 - 1 = 0
 * Uses Newton's method with optimized convergence detection
 * Formula derived from Newton-Raphson iteration method
 */
double	newton_fractal(double z_re, double z_im, int max_iter)
{
	double	next_real;
	double	next_imag;
	double	magnitude_squared;
	int		iteration;

	iteration = 0;
	while (iteration < max_iter)
	{
		magnitude_squared = z_re * z_re + z_im * z_im;
		if (magnitude_squared < 1e-30)
			break ;
		next_real = (2.0 * z_re) / 3.0 + ((z_re * z_re - z_im * z_im)
				/ (magnitude_squared * magnitude_squared)) / 3.0;
		next_imag = (2.0 * z_im) / 3.0 - ((2.0 * z_re * z_im)
				/ (magnitude_squared * magnitude_squared)) / 3.0;
		if (((next_real - z_re) * (next_real - z_re) + (next_imag - z_im)
				* (next_imag - z_im)) < 1e-12)
			break ;
		z_re = next_real;
		z_im = next_imag;
		iteration++;
	}
	if (iteration == max_iter)
		return ((double)max_iter);
	return ((double)iteration);
}
