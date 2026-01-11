/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zotaj-di <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:19:31 by zotaj-di          #+#    #+#             */
/*   Updated: 2025/11/16 15:51:10 by zotaj-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * @brief Prints psychedelic ASCII art header
 */

static void	print_psychedelic_header(void)
{
	ft_putstr_fd("\033[38;5;196m", 1);
	ft_putstr_fd(" ███████╗██████╗ █████╗  ██████╗ ████████╗ ██████╗ ██╗     \n",
		1);
	ft_putstr_fd("\033[38;5;202m", 1);
	ft_putstr_fd(" ██╔════╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔═══██╗██║     \n",
		1);
	ft_putstr_fd("\033[38;5;208m", 1);
	ft_putstr_fd(" █████╗  ██████╔╝███████║██║        ██║   ██║   ██║██║     \n",
		1);
	ft_putstr_fd("\033[38;5;214m", 1);
	ft_putstr_fd(" ██╔══╝  ██╔══██╗██╔══██║██║        ██║   ██║   ██║██║     \n",
		1);
	ft_putstr_fd("\033[38;5;220m", 1);
	ft_putstr_fd(" ██║     ██║  ██║██║  ██║╚██████╗   ██║   ╚██████╔╝███████╗\n",
		1);
	ft_putstr_fd("\033[38;5;226m", 1);
	ft_putstr_fd(" ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚══════╝\n",
		1);
	ft_putstr_fd("\033[0m", 1);
}

/**
 * @brief Prints fractal examples with colorful descriptions
 */
static void	print_fractal_examples(void)
{
	ft_putstr_fd("\033[38;5;196m👽 MANDELBROT\033[0m - Amnesia.. How HIGH ☮️",
		1);
	ft_putstr_fd("\033[2m\n   ./fractol mandelbrot\033[0m\n\n", 1);
	ft_putstr_fd("\033[38;5;51m🌀 JULIA\033[0m - MDMA ecstasy TRIP 💊 ", 1);
	ft_putstr_fd("(requires 2 params)\n", 1);
	ft_putstr_fd("   \033[2m./fractol julia -0.7 0.27015\033[0m", 1);
	ft_putstr_fd("  \033[3m ← Classic\033[0m\n", 1);
	ft_putstr_fd("   \033[2m./fractol julia -0.75 0.11\033[0m", 1);
	ft_putstr_fd("     \033[3m← Spiral\033[0m\n", 1);
	ft_putstr_fd("   \033[2m./fractol julia 0.285 0.01\033[0m", 1);
	ft_putstr_fd("     \033[3m← Lightning\033[0m\n", 1);
	ft_putstr_fd("   \033[2m./fractol julia -0.4 0.6\033[0m", 1);
	ft_putstr_fd("       \033[3m← Dragon\033[0m\n", 1);
	ft_putstr_fd("   \033[2m./fractol julia -0.8 0.156\033[0m", 1);
	ft_putstr_fd("     \033[3m← Rabbit\033[0m\n\n", 1);
	ft_putstr_fd("\033[38;5;129m🪐 NEWTON FRACTALS\033[0m - LSD effects 👅 ☣️\n",
		1);
	ft_putstr_fd("   \033[2m./fractol newton\033[0m\n\n", 1);
	ft_putstr_fd("\033[38;5;219m🌸 MANDEL FLOWER\033[0m - Blooming Mushrooms 🍄 ",
		1);
	ft_putstr_fd("\033[2m\n   ./fractol flower\033[0m\n\n", 1);
}

/**
 * @brief Prints colorful control instructions
 */
static void	print_controls(void)
{
	ft_putstr_fd("\033[38;5;226m⌨ CONTROLS:\033[0m\n", 1);
	ft_putstr_fd("   🖱️  \033[11m Mouse wheel\033[0m     → Zoom in/out\n", 1);
	ft_putstr_fd("  ⬅️➡️  \033[1mArrow keys\033[0m      → Pan view\n", 1);
	ft_putstr_fd("   ↖  \033[1m  Space\033[0m           → Julia mouse", 1);
	ft_putstr_fd(" follow\n", 1);
	ft_putstr_fd("   🌈  \033[1m +/-\033[0m             → Cycle color", 1);
	ft_putstr_fd(" palettes\n", 1);
	ft_putstr_fd("   🔄  \033[1m R\033[0m               → Reset view\n", 1);
	ft_putstr_fd("   ❌  \033[1m ESC\033[0m             → Exit\n\n", 1);
}

/**
 * @brief Prints psychedelic usage information with beautiful ASCII art
 *
 * Creates an immersive, colorful experience
 */
void	print_usage(void)
{
	ft_putstr_fd("\n", 1);
	print_psychedelic_header();
	ft_putstr_fd("\n\033[38;5;51m    ▸ Where You Will Lose ", 1);
	ft_putstr_fd("Contact With Life ◂\033[0m\n", 1);
	ft_putstr_fd("\033[2m    Usage: ./fractol <fractal_type> ", 1);
	ft_putstr_fd("[params]\033[0m\n\n", 1);
	print_fractal_examples();
	print_controls();
	ft_putstr_fd("\033[38;5;129m …. ( 𖦹 ‸𖦹 ).. Let's Dive into the", 1);
	ft_putstr_fd(" infinite...\033[0m\n\n", 1);
}
