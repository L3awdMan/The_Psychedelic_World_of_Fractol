/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:18:56 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/13 17:19:02 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Returns psychedelic color scheme names
 *
 * @param palette Color palette index
 * @return String containing color scheme name
 */
char	*get_color_scheme_name(int palette)
{
	if (palette == 0)
		return ("Neon Pink");
	else if (palette == 1)
		return ("Electric Blue");
	else if (palette == 2)
		return ("Acid Green");
	else if (palette == 3)
		return ("Solar Flare");
	else if (palette == 4)
		return ("Deep Purple");
	else if (palette == 5)
		return ("Cosmic");
	else if (palette == 6)
		return ("Plasma Storm");
	else
		return ("Psychedelic");
}

/**
 * @brief Draws text with black shadow for enhanced readability
 *
 * @param app Pointer to application structure
 * @param x X coordinate for text position
 * @param y Y coordinate for text position
 * @param text Text string to draw
 */
void	draw_text_with_shadow(t_app *app, int x, int y, char *text)
{
	mlx_string_put(app->mlx, app->win, x + 1, y + 1, 0x000000, text);
}

/**
 * @brief Draws semi-transparent rectangle background for text
 *
 * @param app Pointer to application structure
 * @param x X coordinate of rectangle top-left corner
 * @param y Y coordinate of rectangle top-left corner
 * @param size Size parameter for rectangle dimensions
 */
void	draw_background_rect(t_app *app, int x, int y, int size)
{
	int	i;
	int	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < (size * 2))
		{
			mlx_pixel_put(app->mlx, app->win, x + i, y + j, 0x40000000);
			i++;
		}
		j++;
	}
}

/**
 * @brief Beautiful HUD with rectangle background and enhanced readability
 *
 * @param app Pointer to application structure
 */
void	draw_hud(t_app *app)
{
	char	*fractal_name;
	char	zoom_buffer[64];
	char	*color_scheme;
	double	zoom_factor;

	draw_background_rect(app, 10, 15, 75);
	fractal_name = get_fractal_name(app->type);
	zoom_factor = app->initial_scale / app->view.scale;
	format_zoom(zoom_buffer, sizeof(zoom_buffer), zoom_factor);
	color_scheme = get_color_scheme_name(app->current_palette);
	draw_text_with_shadow(app, 20, 30, fractal_name);
	mlx_string_put(app->mlx, app->win, 20, 30, 0x00FFFF, fractal_name);
	draw_text_with_shadow(app, 20, 55, zoom_buffer);
	mlx_string_put(app->mlx, app->win, 20, 55, 0xFFFF00, zoom_buffer);
	draw_text_with_shadow(app, 20, 80, color_scheme);
	mlx_string_put(app->mlx, app->win, 20, 80, 0xFF00FF, color_scheme);
}
