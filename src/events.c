/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:48:19 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:48:19 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Zooms into or out of a specific point while keeping that point centered
 *
 * Maintains smooth zoom behavior by adjusting center coordinates
 *
 * @param app Pointer to application structure
 * @param x X coordinate of zoom center
 * @param y Y coordinate of zoom center
 * @param zoom_factor Factor by which to zoom (>1 = zoom in, <1 = zoom out)
 */
void	zoom_at_point(t_app *app, int x, int y, double zoom_factor)
{
	double	mouse_real_coord;
	double	mouse_imag_coord;

	mouse_real_coord = map_pixel_to_real(app, x);
	mouse_imag_coord = map_pixel_to_imaginary(app, y);
	app->view.scale /= zoom_factor;
	app->view.cx = mouse_real_coord + (app->view.cx - mouse_real_coord)
		/ zoom_factor;
	app->view.cy = mouse_imag_coord + (app->view.cy - mouse_imag_coord)
		/ zoom_factor;
	app->view.max_it = calculate_optimal_iterations(app->view.scale);
	app->needs_redraw = 1;
}

/**
 * @brief Updates Julia set parameters based on mouse position
 *
 * Maps mouse coordinates to complex plane for real-time exploration
 *
 * @param app Pointer to application structure
 * @param x X mouse coordinate
 * @param y Y mouse coordinate
 */
void	set_julia_parameters_from_mouse(t_app *app, int x, int y)
{
	app->julia_real = map_pixel_to_real(app, x);
	app->julia_imag = map_pixel_to_imaginary(app, y);
	app->needs_redraw = 1;
}

/**
 * @brief Handles arrow key navigation to pan the fractal view
 *
 * @param keycode Key code of pressed arrow key
 * @param app Pointer to application structure
 */
static void	handle_navigation_keys(int keycode, t_app *app)
{
	if (keycode == 65364)
		app->view.cy -= PAN_PIXELS * app->view.scale;
	else if (keycode == 65362)
		app->view.cy += PAN_PIXELS * app->view.scale;
	else if (keycode == 65361)
		app->view.cx -= PAN_PIXELS * app->view.scale;
	else if (keycode == 65363)
		app->view.cx += PAN_PIXELS * app->view.scale;
}

/**
 * @brief Handles color palette and mode switching keys
 *
 * @param keycode Key code of pressed key
 * @param app Pointer to application structure
 */
static void	handle_display_keys(int keycode, t_app *app)
{
	if (keycode == 32)
		app->julia_mouse_follow = !app->julia_mouse_follow;
	else if (keycode == 61)
		app->current_palette = (app->current_palette + 1) % PALETTES;
	else if (keycode == 45)
		app->current_palette = (app->current_palette - 1 + PALETTES) % PALETTES;
	else if (keycode == 114)
	{
		app->view.cx = 0.0;
		app->view.cy = 0.0;
		app->view.scale = app->initial_scale;
		app->view.max_it = calculate_optimal_iterations(app->view.scale);
	}
}

/**
 * @brief Main keyboard event handler
 *
 * Processes all keyboard input and delegates to specific handlers
 *
 * @param keycode Key code of pressed key
 * @param param Pointer to application structure (cast from void*)
 * @return Always returns 0
 */
int	handle_keypress_event(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == 65307)
		handle_window_close(app);
	else
	{
		handle_navigation_keys(keycode, app);
		handle_display_keys(keycode, app);
		app->needs_redraw = 1;
	}
	return (0);
}
