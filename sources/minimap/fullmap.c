/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:22 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>
#include <stdint.h>

static int	get_full_map_cell_color(t_engine *eng, int map_x, int map_y)
{
	int	color;

	if (!eng || !eng->map)
		return (MINIMAP_EXTERNAL_COLOR);
	if (map_x < 0 || map_y < 0 || map_x >= eng->map_w || map_y >= eng->map_h)
		color = MINIMAP_EXTERNAL_COLOR;
	else if (eng->map[map_y][map_x] == '1')
		color = MINIMAP_WALL_COLOR;
	else if (eng->map[map_y][map_x] == 'D')
		color = MINIMAP_DOOR_COLOR;
	else
		color = MINIMAP_FLOOR_COLOR;
	if (eng->explored_map && map_x >= 0 && map_y >= 0
		&& map_x < eng->map_w && map_y < eng->map_h
		&& !eng->explored_map[map_y][map_x])
		color = MINIMAP_FOG_COLOR;
	return (color);
}

static void	draw_full_map_cell(t_engine *eng, int map_x, int map_y)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	if (!eng || !eng->map)
		return ;
	start_x = (map_x * eng->win_w) / eng->map_w;
	start_y = (map_y * eng->win_h) / eng->map_h;
	color = get_full_map_cell_color(eng, map_x, map_y);
	x = start_x;
	while (x <= ((map_x + 1) * eng->win_w) / eng->map_w - 1)
	{
		y = start_y;
		while (y <= ((map_y + 1) * eng->win_h) / eng->map_h - 1)
		{
			mlx_put_pixel(eng->img.frame, x, y, color);
			y = y + 1;
		}
		x = x + 1;
	}
}

static void	draw_player_on_full_map(t_engine *eng)
{
	int	center_x;
	int	center_y;
	int	ox;
	int	oy;

	if (!eng || !eng->img.frame)
		return ;
	center_x = (int)((eng->player.pos_x * eng->win_w) / eng->map_w);
	center_y = (int)((eng->player.pos_y * eng->win_h) / eng->map_h);
	ox = -5;
	while (ox <= 5)
	{
		oy = -5;
		while (oy <= 5)
		{
			if (center_x + ox >= 0 && center_x + ox < eng->win_w
				&& center_y + oy >= 0 && center_y + oy < eng->win_h)
				mlx_put_pixel(eng->img.frame, center_x + ox, center_y + oy,
					MINIMAP_PLAYER_COLOR);
			oy = oy + 1;
		}
		ox = ox + 1;
	}
}

void	handle_fullmap_view(t_engine *eng)
{
	int	key_pressed;

	if (!eng)
		return ;
	key_pressed = mlx_is_key_down(eng->mlx, MLX_KEY_R);
	if (key_pressed && !eng->fullmap_toggle)
		eng->fullmap_visible = !eng->fullmap_visible;
	eng->fullmap_toggle = key_pressed;
}

void	draw_full_map(t_engine *eng)
{
	int	map_col;
	int	map_row;

	if (!eng || !eng->img.frame || !eng->map || !eng->fullmap_visible)
		return ;
	map_col = 0;
	while (map_col < eng->map_w)
	{
		map_row = 0;
		while (map_row < eng->map_h)
		{
			draw_full_map_cell(eng, map_col, map_row);
			map_row = map_row + 1;
		}
		map_col = map_col + 1;
	}
	draw_player_on_full_map(eng);
}
