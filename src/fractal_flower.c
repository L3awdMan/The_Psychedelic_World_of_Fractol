/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_flower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:48:41 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:48:41 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * Performs one Mandel Flower iteration step
 * Optimized inline calculation for maximum performance
 */
static void	flower_step(double *z_re, double *z_im, double c_re, double c_im)
{
	double	temp_re;
	double	z_re2;
	double	z_im2;
	double	z_re4;
	double	z_im4;

	temp_re = *z_re;
	z_re2 = (*z_re) * (*z_re);
	z_im2 = (*z_im) * (*z_im);
	z_re4 = z_re2 * z_re2;
	z_im4 = z_im2 * z_im2;
	*z_re = z_re4 * z_re2 - (15.0 * z_re4 * z_im2) + (15.0 * z_re2 * z_im4)
		- z_im4 * z_im2 + c_im;
	*z_im = (6.0 * z_re4 * temp_re * (*z_im)) - (20.0 * z_re2 * temp_re * z_im2
			* (*z_im)) + (6.0 * temp_re * z_im4 * (*z_im)) + c_re;
}

/*
 * Fast escape check for Mandel Flower
 * Returns 1 if escaped, 0 if not
 */
static int	flower_escaped(double z_re, double z_im)
{
	double	z_re2;
	double	z_im2;

	z_re2 = z_re * z_re;
	z_im2 = z_im * z_im;
	if (z_re2 + z_im2 > 4.0)
		return (1);
	return (0);
}

/*
 * Mandel Flower fractal - optimized for performance
 * Uses inline calculations for maximum speed
 */
double	mandel_flower(double c_re, double c_im, int max_iter)
{
	double	z_re;
	double	z_im;
	int		iter;

	z_re = 0.0;
	z_im = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		if (flower_escaped(z_re, z_im))
			return (calculate_smooth_iteration(z_re, z_im, iter));
		flower_step(&z_re, &z_im, c_re, c_im);
		iter++;
	}
	return (max_iter);
}
