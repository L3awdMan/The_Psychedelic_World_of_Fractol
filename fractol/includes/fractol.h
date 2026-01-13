/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/11/16 15:26:55 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

/** @brief Window dimensions for rendering */
/** @details Window width in pixels */
#define WIDTH 1100
/** @details Window height in pixels */
# define WIDTH 1100
# define HEIGHT 800

/** @brief Zoom step factor for scaling */
#define ZOOM_STEP 1.1
/** @brief Number of pixels to pan when moving */
# define ZOOM_STEP 1.1
# define PAN_PIXELS 50

/** @brief Total number of available color palettes */
# define PALETTES 8

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

/** @brief Enumeration of supported fractal types */
/**
 * @enum e_type
 * @brief Available fractal algorithms
 */
typedef enum e_type
{
	FRACT_MANDEL,
	FRACT_JULIA,
	FRACT_NEWTON3,
	FRACT_MANDEL_FLOWER
}				t_type;

/**
 * @struct s_img
 * @brief Image structure for MiniLibX pixel manipulation
 */
typedef struct s_img
{
	void		*id;
	char		*data;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

/**
 * @struct s_view
 * @brief View parameters for fractal rendering in complex plane
 */
typedef struct s_view
{
	double		cx;
	double		cy;
	double		scale;
	int			max_it;
}				t_view;

/**
 * @struct s_app
 * @brief Main application state and configuration
 */
typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_type		type;
	t_view		view;
	double		julia_real;
	double		julia_imag;
	int			julia_mouse_follow;
	double		initial_scale;
	int			needs_redraw;
	int			is_dragging;
	int			last_mouse_x;
	int			last_mouse_y;
	int			current_palette;
}				t_app;

/** @brief Fractal calculation functions */
/**
 * @brief Calculate Mandelbrot fractal escape value
 * @param c_re Real part of complex number
 * @param c_im Imaginary part of complex number
 * @param max_iter Maximum iterations before escape
 * @return Smooth iteration count
 */
double			mandelbrot(double c_re, double c_im, int max_iter);
/**
 * @brief Calculate Julia set fractal escape value
 * @param z_re Real part of initial z value
 * @param z_im Imaginary part of initial z value
 * @param max_iter Maximum iterations before escape
 * @param app Application context containing Julia parameters
 * @return Smooth iteration count
 */
double			mister_julia(double z_re, double z_im, int max_iter,
					const t_app *app);
/**
 * @brief Calculate Newton fractal escape value
 * @param z_re Real part of initial z value
 * @param z_im Imaginary part of initial z value
 * @param max_iter Maximum iterations before convergence
 * @return Smooth iteration count
 */
double			newton_fractal(double z_re, double z_im, int max_iter);
/**
 * @brief Calculate Mandelbrot flower fractal escape value
 * @param z_re Real part of initial z value
 * @param z_im Imaginary part of initial z value
 * @param max_iter Maximum iterations before escape
 * @return Smooth iteration count
 */
double			mandel_flower(double z_re, double z_im, int max_iter);

/**
 * @brief Calculate smooth iteration count for anti-aliasing
 * @param z_re Final z real value
 * @param z_im Final z imaginary value
 * @param iter Number of iterations completed
 * @return Smoothed iteration value
 */
double			calculate_smooth_iteration(double z_re, double z_im, int iter);

/**
 * @brief Generate color for fractal point
 * @param smooth_iter Smooth iteration count
 * @param max_it Maximum iterations
 * @param palette_mode Color palette index
 * @return RGB color value
 */
unsigned int	generate_fractal_color(double smooth_iter, int max_it,
					int palette_mode);

/** @brief Color utility functions */
/**
 * @brief Clamp value between 0 and 1
 * @param value Input value
 * @return Clamped value
 */
double			clamp(double value);
/**
 * @brief Convert RGB values to integer color
 * @param r Red component (0.0-1.0)
 * @param g Green component (0.0-1.0)
 * @param b Blue component (0.0-1.0)
 * @return Integer RGB color
 */
unsigned int	rgb_to_int(double r, double g, double b);
/**
 * @brief Generate color using cosine palette
 * @param t Parameter value (0.0-1.0)
 * @param mode Palette variation
 * @return RGB color value
 */
unsigned int	cosine_palette(double t, int mode);
/**
 * @brief Generate psychedelic color palette
 * @param t Parameter value (0.0-1.0)
 * @return RGB color value
 */
unsigned int	psychedelic_palette(double t);
/**
 * @brief Apply intensity scaling to color
 * @param base_color Base RGB color
 * @param intensity Intensity multiplier
 * @return Scaled RGB color
 */
unsigned int	apply_intensity_scaling(unsigned int base_color,
					double intensity);

/** @brief Rendering functions */
/**
 * @brief Render color for single pixel
 * @param app Application context
 * @param x Pixel x coordinate
 * @param y Pixel y coordinate
 * @param max_iter Maximum iterations
 * @return RGB color value
 */
unsigned int	render_pixel_color(t_app *app, int x, int y, int max_iter);
/**
 * @brief Render complete fractal frame
 * @param app Application context
 */
void			render_complete_frame(t_app *app);

/** @brief Coordinate mapping functions */
/**
 * @brief Map pixel x to real coordinate
 * @param app Application context
 * @param x Pixel x coordinate
 * @return Real coordinate in complex plane
 */
double			map_pixel_to_real(t_app *app, int x);
/**
 * @brief Map pixel y to imaginary coordinate
 * @param app Application context
 * @param y Pixel y coordinate
 * @return Imaginary coordinate in complex plane
 */
double			map_pixel_to_imaginary(t_app *app, int y);

/** @brief Zoom and interaction functions */
/**
 * @brief Zoom at specific point
 * @param app Application context
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 * @param zoom_factor Zoom multiplication factor
 */
void			zoom_at_point(t_app *app, int x, int y, double zoom_factor);
/**
 * @brief Set Julia parameters from mouse position
 * @param app Application context
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 */
void			set_julia_parameters_from_mouse(t_app *app, int x, int y);

/** @brief Event handling functions */
/**
 * @brief Handle keyboard events
 * @param keycode Key code pressed
 * @param param Application context pointer
 * @return 0 on success
 */
int				handle_keypress_event(int keycode, void *param);
/**
 * @brief Handle mouse button press events
 * @param button Mouse button pressed
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 * @param param Application context pointer
 * @return 0 on success
 */
int				handle_mouse_press(int button, int x, int y, void *param);
/**
 * @brief Handle mouse button release events
 * @param button Mouse button released
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 * @param param Application context pointer
 * @return 0 on success
 */
int				handle_mouse_release(int button, int x, int y, void *param);
/**
 * @brief Handle mouse movement events
 * @param x Mouse x coordinate
 * @param y Mouse y coordinate
 * @param param Application context pointer
 * @return 0 on success
 */
int				handle_mouse_movement(int x, int y, void *param);
/**
 * @brief Handle window close event
 * @param param Application context pointer
 * @return Exit code
 */
int				handle_window_close(void *param);
/**
 * @brief Main rendering loop function
 * @param param Application context pointer
 * @return 0 on success
 */
int				main_render_loop(void *param);

/** @brief Event utility functions */

/** @brief Application lifecycle functions */
/**
 * @brief Initialize application state
 * @param app Application context
 */
void			initialize_application(t_app *app);
/**
 * @brief Clean up application resources
 * @param app Application context
 */
void			cleanup_application(t_app *app);
/**
 * @brief Parse command line arguments
 * @param app Application context
 * @param argc Argument count
 * @param argv Argument vector
 * @return 1 on success, 0 on failure
 */
int				parse_program_args(t_app *app, int argc, char **argv);
/**
 * @brief Print program usage information
 */
void			print_usage(void);

/** @brief Parsing utility functions */
/**
 * @brief Parse decimal part of floating point number
 * @param str Input string
 * @param i Pointer to current position
 * @return Decimal value
 */
double			parse_decimal_part(const char *str, int *i);
/**
 * @brief Convert string to floating point number
 * @param str Input string
 * @return Floating point value
 */
double			ft_atof(const char *str);

/** @brief UI functions */
/**
 * @brief Draw heads-up display
 * @param app Application context
 */
void			draw_hud(t_app *app);
/**
 * @brief Draw text with shadow effect
 * @param app Application context
 * @param x Text x coordinate
 * @param y Text y coordinate
 * @param text Text string to draw
 */
void			draw_text_with_shadow(t_app *app, int x, int y, char *text);
/**
 * @brief Draw background rectangle
 * @param app Application context
 * @param x Rectangle x coordinate
 * @param y Rectangle y coordinate
 * @param size Rectangle size
 */
void			draw_background_rect(t_app *app, int x, int y, int size);
/**
 * @brief Format zoom level for display
 * @param buf Output buffer
 * @param buf_size Buffer size
 * @param zoom Zoom value
 */
void			format_zoom(char *buf, int buf_size, double zoom);
/**
 * @brief Get fractal type name
 * @param type Fractal type enum
 * @return String name of fractal
 */
char			*get_fractal_name(t_type type);
/**
 * @brief Get color scheme name
 * @param palette Palette index
 * @return String name of color scheme
 */
char			*get_color_scheme_name(int palette);
/**
 * @brief Append string to buffer
 * @param dst Destination buffer
 * @param i Current position
 * @param buf_size Buffer size
 * @param s Source string
 * @return New position in buffer
 */
int				append_str(char *dst, int i, int buf_size, const char *s);
/**
 * @brief Append integer to buffer
 * @param dst Destination buffer
 * @param i Current position
 * @param buf_size Buffer size
 * @param value Integer value
 * @return New position in buffer
 */
int				append_int(char *dst, int i, int buf_size, int value);

/** @brief Utility functions */
/**
 * @brief Set pixel color in image
 * @param img Image structure
 * @param x Pixel x coordinate
 * @param y Pixel y coordinate
 * @param color RGB color value
 */
void			set_pixel_color(t_img *img, int x, int y, unsigned int color);
/**
 * @brief Calculate optimal iteration count for given scale
 * @param scale Current view scale
 * @return Optimal iteration count
 */
int				calculate_optimal_iterations(double scale);

#endif
