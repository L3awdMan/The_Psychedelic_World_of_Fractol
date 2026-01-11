/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:20:02 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:20:02 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Handles mouse button press events including zoom and drag initiation
 *
 * Mouse wheel up/down: zoom in/out at cursor position
 * Left click: initiates dragging for view panning
 *
 * @param button Mouse button identifier (1=left, 4=wheel up, 5=wheel down)
 * @param x X coordinate of mouse cursor
 * @param y Y coordinate of mouse cursor
 * @param param Pointer to application structure (cast from void*)
 * @return Always returns 0
 */
int	handle_mouse_press(int button, int x, int y, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (button == 4)
		zoom_at_point(app, x, y, ZOOM_STEP);
	else if (button == 5)
		zoom_at_point(app, x, y, 1.0 / ZOOM_STEP);
	else if (button == 1)
	{
		app->is_dragging = 1;
		app->last_mouse_x = x;
		app->last_mouse_y = y;
	}
	return (0);
}

/**
 * @brief Handles mouse button release events
 *
 * Terminates dragging state when left mouse button is released
 *
 * @param button Mouse button identifier
 * @param x X coordinate of mouse cursor (unused)
 * @param y Y coordinate of mouse cursor (unused)
 * @param param Pointer to application structure (cast from void*)
 * @return Always returns 0
 */
int	handle_mouse_release(int button, int x, int y, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)x;
	(void)y;
	if (button == 1)
		app->is_dragging = 0;
	return (0);
}

/**
 * @brief Handles mouse movement events for interactive features
 *
 * Updates Julia parameters during mouse follow mode
 * Pans fractal view when dragging is active
 *
 * @param x Current X coordinate of mouse cursor
 * @param y Current Y coordinate of mouse cursor
 * @param param Pointer to application structure (cast from void*)
 * @return Always returns 0
 */
int	handle_mouse_movement(int x, int y, void *param)
{
	t_app	*app;
	double	delta_x;
	double	delta_y;

	app = (t_app *)param;
	if (app->type == FRACT_JULIA && app->julia_mouse_follow)
		set_julia_parameters_from_mouse(app, x, y);
	if (app->is_dragging)
	{
		delta_x = (x - app->last_mouse_x) * app->view.scale;
		delta_y = (y - app->last_mouse_y) * app->view.scale;
		app->view.cx -= delta_x;
		app->view.cy += delta_y;
		app->last_mouse_x = x;
		app->last_mouse_y = y;
		app->needs_redraw = 1;
	}
	return (0);
}

/**
 * @brief Handles window close event from title bar close button
 *
 * Ensures proper cleanup before program termination
 *
 * @param param Pointer to application structure (cast from void*)
 * @return Does not return (calls exit)
 */
int	handle_window_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	cleanup_application(app);
	exit(0);
}

/**
 * @brief Main rendering loop executed continuously
 *
 * Redraws fractal and UI when changes are detected
 *
 * @param param Pointer to application structure (cast from void*)
 * @return Always returns 0
 */
int	main_render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->needs_redraw)
	{
		render_complete_frame(app);
		mlx_put_image_to_window(app->mlx, app->win, app->img.id, 0, 0);
		draw_hud(app);
		app->needs_redraw = 0;
	}
	return (0);
}
