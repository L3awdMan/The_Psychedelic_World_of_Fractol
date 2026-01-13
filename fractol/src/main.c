/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:49:45 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 15:49:45 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	init_mlx(t_app *app);
static void	setup_hooks(t_app *app);

/**
 * @brief Main program entry point
 *
 * Parses arguments, initializes application, and starts main loop
 *
 * @param ac Number of command line arguments
 * @param av Array of command line argument strings
 * @return 0 on success, 1 on failure
 */
int	main(int ac, char **av)
{
	t_app	app;

	initialize_application(&app);
	if (!parse_program_args(&app, ac, av))
		return (1);
	if (!init_mlx(&app))
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", 2);
		cleanup_application(&app);
		return (1);
	}
	setup_hooks(&app);
	render_complete_frame(&app);
	mlx_put_image_to_window(app.mlx, app.win, app.img.id, 0, 0);
	draw_hud(&app);
	mlx_loop(app.mlx);
	return (0);
}

/**
 * @brief Initializes MiniLibX connection and creates window
 *
 * Sets up image buffer for fast pixel manipulation
 *
 * @param app Pointer to application structure
 * @return 1 on success, 0 on failure
 */
static int	init_mlx(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (0);
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT,
			"Psychedelic World of Fractol");
	if (!app->win)
		return (0);
	app->img.id = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	if (!app->img.id)
		return (0);
	app->img.data = mlx_get_data_addr(app->img.id, &app->img.bits_per_pixel,
			&app->img.line_len, &app->img.endian);
	return (1);
}

/**
 * @brief Sets up all event hooks for user interaction
 *
 * Connects keyboard, mouse, and window events to handler functions
 *
 * @param app Pointer to application structure
 */
static void	setup_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, handle_keypress_event, app);
	mlx_hook(app->win, 4, 1L << 2, handle_mouse_press, app);
	mlx_hook(app->win, 5, 1L << 3, handle_mouse_release, app);
	mlx_hook(app->win, 6, 1L << 6, handle_mouse_movement, app);
	mlx_hook(app->win, 17, 1L << 17, handle_window_close, app);
	mlx_loop_hook(app->mlx, main_render_loop, app);
}
