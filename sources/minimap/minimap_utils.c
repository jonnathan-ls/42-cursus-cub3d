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
