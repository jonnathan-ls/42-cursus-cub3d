/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_health.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:46:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/**
 * Returns color based on health percentage.
 * @param health Player health value (0-100).
 * @return RGBA color (green, yellow, or red).
 */
static uint32_t	get_health_color(int health)
{
	if (health > 60)
		return (0xFF00FF00);
	else if (health > 30)
		return (0xFFFFAA00);
	else
		return (0xFFFF0000);
}

/**
 * Fills one horizontal line of health bar.
 * @param pixels Frame pixel buffer.
 * @param y Y coordinate of line.
 * @param w Window width.
 * @param params Array with bar width, window width, health.
 */
static void	fill_bar_line(uint32_t *pixels, int y, int w, int params[3])
{
	int			x;
	uint32_t	color;

	color = get_health_color(params[2]);
	x = 10;
	while (x < 205)
	{
		if (x - 10 < params[0])
			pixels[y * w + x] = color;
		else
			pixels[y * w + x] = 0xFF333333;
		x = x + 1;
	}
}

/**
 * Draws filled portion of health bar.
 * @param pixels Frame pixel buffer.
 * @param width Window width.
 * @param health Player health value (0-100).
 */
static void	draw_health_bar_fill(uint32_t *pixels, int width, int health)
{
	int	y;
	int	params[3];

	params[0] = (health * 190) / 100;
	params[1] = width;
	params[2] = health;
	y = 10;
	while (y < 30)
	{
		fill_bar_line(pixels, y, width, params);
		y = y + 1;
	}
}

/**
 * Draws white border around health bar.
 * @param pixels Frame pixel buffer.
 * @param width Window width.
 */
static void	draw_health_bar_border(uint32_t *pixels, int width)
{
	int	x;
	int	y;

	y = 8;
	while (y < 32)
	{
		x = 8;
		while (x < 208)
		{
			if (y == 8 || y == 31 || x == 8 || x == 207)
				pixels[y * width + x] = 0xFFFFFFFF;
			x = x + 1;
		}
		y = y + 1;
	}
}

/**
 * Renders player health bar in top-left corner.
 * @param eng Pointer to engine structure.
 */
void	draw_health_bar(t_engine *eng)
{
	uint32_t	*pixels;

	if (!eng || !eng->frame)
		return ;
	pixels = (uint32_t *)eng->frame->pixels;
	draw_health_bar_border(pixels, eng->window_width);
	draw_health_bar_fill(pixels, eng->window_width, eng->player.health);
}
