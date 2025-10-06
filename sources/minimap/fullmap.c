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
#include "shared.h"
#include <MLX42/MLX42.h>

/**
 * @brief Determines the color of a full map cell based on its type.
 *
 * Returns appropriate color for walls, doors, floors, or fog of war
 * depending on cell position, map content, and exploration state.
 *
 * @param eng Engine structure containing map and exploration data.
 * @param map_x X coordinate of the map cell.
 * @param map_y Y coordinate of the map cell.
 * @return Color value for the cell.
 */
static int	get_full_map_cell_color(t_engine *eng, int map_x, int map_y)
{
	int	color;

	if (!eng || !eng->map)
		return (MINIMAP_EXTERNAL_COLOR);
	if (map_x < 0 || map_y < 0
		|| map_x >= eng->map_width || map_y >= eng->map_height)
		color = MINIMAP_EXTERNAL_COLOR;
	else if (eng->map[map_y][map_x] == '1')
		color = MINIMAP_WALL_COLOR;
	else if (eng->map[map_y][map_x] == 'D')
		color = MINIMAP_DOOR_COLOR;
	else
		color = MINIMAP_FLOOR_COLOR;
	if (eng->explored_map && map_x >= 0 && map_y >= 0
		&& map_x < eng->map_width && map_y < eng->map_height
		&& !eng->explored_map[map_y][map_x])
		color = MINIMAP_FOG_COLOR;
	return (color);
}

/**
 * @brief Draws a single cell of the full map overlay.
 *
 * Computes screen coordinates for the cell, determines its color, and
 * fills the corresponding screen area with that color.
 *
 * @param eng Engine structure containing map and frame buffer.
 * @param map_x X coordinate of the map cell.
 * @param map_y Y coordinate of the map cell.
 */
static void	draw_full_map_cell(t_engine *eng, int map_x, int map_y)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	if (!eng || !eng->map)
		return ;
	start_x = (map_x * eng->window_width) / eng->map_width;
	start_y = (map_y * eng->window_height) / eng->map_height;
	color = get_full_map_cell_color(eng, map_x, map_y);
	x = start_x;
	while (x <= ((map_x + TEXTURE_CLAMP_ONE) * eng->window_width)
		/ eng->map_width - TEXTURE_CLAMP_ONE)
	{
		y = start_y;
		while (y <= ((map_y + TEXTURE_CLAMP_ONE) * eng->window_height)
			/ eng->map_height - TEXTURE_CLAMP_ONE)
		{
			mlx_put_pixel(eng->frame, x, y, color);
			y = y + 1;
		}
		x = x + 1;
	}
}

/**
 * @brief Draws the player indicator on the full map.
 *
 * Computes player screen position and draws a colored square around the
 * player's location on the full map overlay.
 *
 * @param eng Engine structure containing player position and frame.
 */
static void	draw_player_on_full_map(t_engine *eng)
{
	int	center_x;
	int	center_y;
	int	ox;
	int	oy;

	if (!eng || !eng->frame)
		return ;
	center_x = (int)((eng->player.pos_x * eng->window_width)
			/ eng->map_width);
	center_y = (int)((eng->player.pos_y * eng->window_height)
			/ eng->map_height);
	ox = -FULLMAP_PLAYER_SIZE;
	while (ox <= FULLMAP_PLAYER_SIZE)
	{
		oy = -FULLMAP_PLAYER_SIZE;
		while (oy <= FULLMAP_PLAYER_SIZE)
		{
			if (is_within_bounds(center_x + ox, 0, eng->window_width)
				&& is_within_bounds(center_y + oy, 0, eng->window_height))
				mlx_put_pixel(eng->frame, center_x + ox, center_y + oy,
					MINIMAP_PLAYER_COLOR);
			oy = oy + 1;
		}
		ox = ox + 1;
	}
}

/**
 * @brief Toggles full map view on R key press.
 *
 * Detects R key press and toggles the fullmap_visible flag, using a
 * toggle flag to prevent rapid state changes from continuous key press.
 *
 * @param eng Engine structure containing fullmap visibility state.
 */
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

/**
 * @brief Renders the full map overlay covering the entire screen.
 *
 * Iterates through all map cells, draws each cell with appropriate
 * color, and places the player indicator if fullmap is visible.
 *
 * @param eng Engine structure containing map, frame, and visibility.
 */
void	draw_full_map(t_engine *eng)
{
	int	map_col;
	int	map_row;

	if (!eng || !eng->frame || !eng->map || !eng->fullmap_visible)
		return ;
	map_col = 0;
	while (map_col < eng->map_width)
	{
		map_row = 0;
		while (map_row < eng->map_height)
		{
			draw_full_map_cell(eng, map_col, map_row);
			map_row = map_row + 1;
		}
		map_col = map_col + 1;
	}
	draw_player_on_full_map(eng);
}
