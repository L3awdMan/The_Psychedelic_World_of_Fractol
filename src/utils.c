/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:18:33 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:18:33 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Calculates optimal iteration count based on current zoom level
 *
 * Higher zoom levels require more iterations for accurate detail
 * Returns appropriate iteration count for current scale
 *
 * @param scale Current zoom scale factor
 * @return Optimal iteration count for the given scale
 */
int	calculate_optimal_iterations(double scale)
{
	double	zoom_level;

	zoom_level = 1.0 / scale;
	if (zoom_level < 1.0)
		return (50);
	else if (zoom_level < 10.0)
		return (80);
	else if (zoom_level < 100.0)
		return (120);
	else if (zoom_level < 1000.0)
		return (200);
	else
		return (300);
}

/**
 * @brief Initializes application with default fractal parameters
 *
 * Sets up initial view settings and fractal configuration
 *
 * @param app Pointer to application structure to initialize
 */
void	initialize_application(t_app *app)
{
	app->mlx = NULL;
	app->win = NULL;
	app->img.id = NULL;
	app->type = FRACT_MANDEL;
	app->view.cx = 0.0;
	app->view.cy = 0.0;
	app->view.scale = 0.005;
	app->initial_scale = app->view.scale;
	app->view.max_it = calculate_optimal_iterations(app->view.scale);
	app->julia_real = -0.7;
	app->julia_imag = 0.27015;
	app->julia_mouse_follow = 0;
	app->needs_redraw = 1;
	app->is_dragging = 0;
	app->last_mouse_x = 0;
	app->last_mouse_y = 0;
	app->current_palette = 0;
}

/**
 * @brief Cleans up application resources and frees allocated memory
 *
 * Properly destroys MiniLibX components in correct order
 *
 * @param app Pointer to application structure to clean up
 */
void	cleanup_application(t_app *app)
{
	if (app->img.id)
		mlx_destroy_image(app->mlx, app->img.id);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
