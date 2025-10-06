/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/01 01:30:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include "shared.h"
#include <math.h>

/**
 * @brief Computes screen position for a map block in the minimap.
 *
 * Transforms map cell coordinates to minimap screen coordinates using
 * player position, direction, and minimap scale.
 *
 * @param eng Engine structure with player data.
 * @param map Minimap structure to update with screen position.
 */
static void	minimap_compute_block_screen_start(t_engine *eng, t_minimap *map)
{
	double	offset_x;
	double	offset_y;
	double	proj_fwd;
	int		start_x;
	int		start_y;

	offset_x = ((double)map->block_cell_x + 0.5)
		- (double)eng->player.pos_x;
	offset_y = ((double)map->block_cell_y + 0.5)
		- (double)eng->player.pos_y;
	proj_fwd = offset_x * eng->player.dir_x;
	proj_fwd = proj_fwd + offset_y * eng->player.dir_y;
	start_x = map->left + map->size / 2;
	start_x = start_x + (int)(((offset_x * -eng->player.dir_y)
				+ (offset_y * eng->player.dir_x)) * (double)map->final_scale);
	start_x = start_x - map->final_scale / 2;
	start_y = map->top + map->size / 2;
	start_y = start_y - (int)(proj_fwd * (double)map->final_scale);
	start_y = start_y - map->final_scale / 2;
	map->block_start_x = start_x;
	map->block_start_y = start_y;
}

/**
 * @brief Prepares rendering data for a specific map block.
 *
 * Determines block color based on map cell type and exploration state,
 * then computes its screen position.
 *
 * @param eng Engine structure with map and exploration data.
 * @param map Minimap structure to update with block data.
 */
static void	minimap_prepare_block(t_engine *eng, t_minimap *map)
{
	char	c;

	if (!eng || !map)
		return ;
	map->block_color = MINIMAP_FOG_COLOR;
	if (map->block_cell_x < 0 || map->block_cell_y < 0)
		return ;
	if (map->block_cell_x >= eng->map_width
		|| map->block_cell_y >= eng->map_height)
		return ;
	c = eng->map[map->block_cell_y][map->block_cell_x];
	if (c == '1')
		map->block_color = MINIMAP_WALL_COLOR;
	if (c == 'D')
		map->block_color = MINIMAP_DOOR_COLOR;
	if (c == '0')
		map->block_color = MINIMAP_FLOOR_COLOR;
	if (eng->explored_map && !eng->explored_map[map->block_cell_y]
		[map->block_cell_x])
		map->block_color = MINIMAP_FOG_COLOR;
	minimap_compute_block_screen_start(eng, map);
}

/**
 * @brief Draws all pixels for a map block on the minimap.
 *
 * Renders the block at its computed screen position, checking boundaries
 * to ensure pixels stay within the minimap area.
 *
 * @param eng Engine structure containing frame buffer.
 * @param map Minimap structure with block data and position.
 */
static void	minimap_draw_block_pixels(t_engine *eng, t_minimap *map)
{
	int	dx;
	int	dy;
	int	pad;
	int	pxp;
	int	pyp;

	pad = 1;
	dx = -pad;
	while (dx < map->final_scale + pad)
	{
		dy = -pad;
		while (dy < map->final_scale + pad)
		{
			pxp = map->block_start_x + dx;
			pyp = map->block_start_y + dy;
			if (pxp >= map->left && pxp < map->left + map->size)
			{
				if (pyp >= map->top && pyp < map->top + map->size)
					mlx_put_pixel(eng->frame, pxp, pyp, map->block_color);
			}
			dy = dy + 1;
		}
		dx = dx + 1;
	}
}

/**
 * @brief Renders all blocks in a vertical column of the minimap.
 *
 * Iterates through tiles vertically around player position, preparing
 * and drawing each block.
 *
 * @param eng Engine structure with map data.
 * @param tile_x X coordinate of the column.
 * @param player_y Y coordinate of player for centering.
 * @param map Minimap structure for rendering data.
 */
static void	minimap_render_column(t_engine *eng,
	int tile_x, int player_y, t_minimap *map)
{
	int	tile_y;
	int	half_tiles;

	half_tiles = 5;
	tile_y = player_y - half_tiles;
	if (tile_y < 0)
		tile_y = 0;
	while (tile_y <= player_y + half_tiles && tile_y < eng->map_height)
	{
		map->block_cell_x = tile_x;
		map->block_cell_y = tile_y;
		minimap_prepare_block(eng, map);
		minimap_draw_block_pixels(eng, map);
		tile_y = tile_y + 1;
	}
}

/**
 * @brief Renders all visible map cells on the minimap.
 *
 * Iterates through map tiles around the player position, rendering each
 * column of blocks within the visible range.
 *
 * @param eng Engine structure with map and player data.
 * @param map Minimap structure for rendering configuration.
 */
void	render_minimap_cells(t_engine *eng, t_minimap *map)
{
	int	tile_x;
	int	player_x;
	int	player_y;

	if (!eng || !map)
		return ;
	player_x = (int)eng->player.pos_x;
	player_y = (int)eng->player.pos_y;
	tile_x = player_x - 5;
	if (tile_x < 0)
		tile_x = 0;
	while (tile_x <= player_x + 5 && tile_x < eng->map_width)
	{
		minimap_render_column(eng, tile_x, player_y, map);
		tile_x = tile_x + 1;
	}
}
