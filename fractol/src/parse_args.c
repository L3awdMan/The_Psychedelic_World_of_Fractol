/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:19:53 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:19:53 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Validates single-parameter fractal types
 *
 * @param ac Argument count
 * @param av Argument vector
 * @return 1 if valid, 0 if invalid
 */
static int	validate_single_param(int ac, char **av)
{
	if (ft_strncmp(av[1], "mandelbrot", 10) == 0 && ac != 2)
	{
		ft_putstr_fd("Error: Mandelbrot takes no additional parameters\n", 2);
		return (0);
	}
	if (ft_strncmp(av[1], "newton", 6) == 0 && ft_strlen(av[1]) == 6 && ac != 2)
	{
		ft_putstr_fd("Error: Newton fractals take no extra parameters\n", 2);
		return (0);
	}
	if (ft_strncmp(av[1], "flower", 6) == 0 && ac != 2)
	{
		ft_putstr_fd("Error: Mandel Flower takes no extra parameters\n", 2);
		return (0);
	}
	return (1);
}

/**
 * @brief Validates argument count for each fractal type
 *
 * Returns 1 if valid, 0 if invalid
 *
 * @param ac Argument count
 * @param av Argument vector
 * @return 1 if valid, 0 if invalid
 */
static int	validate_args_count(int ac, char **av)
{
	if (ft_strncmp(av[1], "julia", 5) == 0 && ac != 4)
	{
		ft_putstr_fd("Error: Julia requires exactly 2 parameters\n", 2);
		return (0);
	}
	return (validate_single_param(ac, av));
}


/**
 * @brief Sets fractal type and parameters based on validated arguments
 *
 * Returns 1 on success, 0 on failure
 *
 * @param app Pointer to application structure
 * @param ac Argument count
 * @param av Argument vector
 * @return 1 on success, 0 on failure
 */
static int	set_fractal_type(t_app *app, int ac, char **av)
{
	(void)ac;
	if (ft_strncmp(av[1], "mandelbrot", 10) == 0)
		app->type = FRACT_MANDEL;
	else if (ft_strncmp(av[1], "julia", 5) == 0)
	{
		app->type = FRACT_JULIA;
		app->julia_real = ft_atof(av[2]);
		app->julia_imag = ft_atof(av[3]);
	}
	else if (ft_strncmp(av[1], "newton", 6) == 0 && ft_strlen(av[1]) == 6)
		app->type = FRACT_NEWTON3;
	else if (ft_strncmp(av[1], "flower", 6) == 0)
		app->type = FRACT_MANDEL_FLOWER;
	else
	{
		ft_putstr_fd("Error: Invalid fractal type\n", 2);
		return (0);
	}
	return (1);
}

/**
 * @brief Parses and validates command line arguments
 *
 * Ensures correct parameter count for each fractal type
 * Returns 1 on success, 0 on failure
 *
 * @param app Pointer to application structure
 * @param ac Argument count from main
 * @param av Argument vector from main
 * @return 1 on success, 0 on failure
 */
int	parse_program_args(t_app *app, int ac, char **av)
{
	if (ac < 2)
	{
		print_usage();
		return (0);
	}
	if (!validate_args_count(ac, av))
	{
		print_usage();
		return (0);
	}
	if (!set_fractal_type(app, ac, av))
	{
		print_usage();
		return (0);
	}
	return (1);
}
