/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 23:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/07 23:47:42 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>

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
void	minimap_prepare_block(t_engine *eng, t_minimap *map)
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
 * @brief Draws a single pixel column for a map block.
 *
 * Renders vertical slice of block pixels at given X position.
 *
 * @param eng Engine structure containing frame buffer.
 * @param map Minimap structure with block data.
 * @param pxp X position of pixel column.
 */
static void	draw_block_column(t_engine *eng, t_minimap *map, int pxp)
{
	int	dy;
	int	pyp;

	dy = -1;
	while (dy < map->final_scale + 1)
	{
		pyp = map->block_start_y + dy;
		if (pyp >= map->top && pyp < map->top + map->size)
			mlx_put_pixel(eng->frame, pxp, pyp, map->block_color);
		dy = dy + 1;
	}
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
void	minimap_draw_block_pixels(t_engine *eng, t_minimap *map)
{
	int	dx;
	int	pxp;

	if (map->block_start_x >= map->left + map->size)
		return ;
	if (map->block_start_y >= map->top + map->size)
		return ;
	dx = -1;
	while (dx < map->final_scale + 1)
	{
		pxp = map->block_start_x + dx;
		if (pxp >= map->left && pxp < map->left + map->size)
			draw_block_column(eng, map, pxp);
		dx = dx + 1;
	}
}
