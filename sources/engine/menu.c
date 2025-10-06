/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:39:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

/**
 * Draws a single row of the menu texture.
 * @param eng Pointer to engine structure.
 * @param start_x Starting X position on screen.
 * @param start_y Starting Y position on screen.
 * @param row Row index in texture.
 */
static void	draw_menu_row(t_engine *eng, int start_x, int start_y, int row)
{
	int	px;
	int	texture_width;
	int	screen_y;

	if (!eng || !eng->tex.menu || !eng->frame)
		return ;
	texture_width = eng->tex.menu->width;
	screen_y = start_y + row;
	px = 0;
	while (px < texture_width)
	{
		mlx_put_pixel(eng->frame, start_x + px, screen_y,
			get_texture_pixel(eng->tex.menu, px, row));
		px = px + 1;
	}
}

/**
 * Handles menu toggle when I key is pressed.
 * @param eng Pointer to engine structure.
 */
void	handle_menu_view(t_engine *eng)
{
	int	key_pressed;

	if (!eng)
		return ;
	key_pressed = mlx_is_key_down(eng->mlx, MLX_KEY_I);
	if (key_pressed && !eng->menu_toggle)
		eng->menu_visible = !eng->menu_visible;
	eng->menu_toggle = key_pressed;
}

/**
 * Renders menu overlay on screen.
 * @param eng Pointer to engine structure.
 */
void	draw_menu_overlay(t_engine *eng)
{
	int	texture_width;
	int	texture_height;
	int	start_x;
	int	start_y;
	int	row;

	if (!eng || !eng->tex.menu || !eng->frame)
		return ;
	texture_width = eng->tex.menu->width;
	texture_height = eng->tex.menu->height;
	start_x = eng->window_width - texture_width - 10;
	start_y = 10;
	row = 0;
	while (row < texture_height)
	{
		draw_menu_row(eng, start_x, start_y, row);
		row = row + 1;
	}
}
