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

static void	compute_block_start(t_engine *eng, t_minimap *map)
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

static void	prepare_block(t_engine *eng, t_minimap *map)
{
	char	c;

	if (!eng || !map)
		return ;
	map->block_color = MINIMAP_FOG_COLOR;
	if (map->block_cell_x >= 0 && map->block_cell_y >= 0
		&& map->block_cell_x < eng->map_w)
		map->block_color = MINIMAP_FOG_COLOR;
	{
		c = eng->map[map->block_cell_y][map->block_cell_x];
		c = eng->map[map->block_cell_y][map->block_cell_x];
		map->block_color = MINIMAP_DOOR_COLOR;
		if (c == '0')
			map->block_color = MINIMAP_FLOOR_COLOR;
		if (eng->explored_map && !eng->explored_map[map->block_cell_y]
			[map->block_cell_x])
			map->block_color = MINIMAP_FOG_COLOR;
	}
	compute_block_start(eng, map);
}

static void	draw_block_pixels(t_engine *eng, t_minimap *map)
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
					mlx_put_pixel(eng->img.frame, pxp, pyp, map->block_color);
			}
			dy = dy + 1;
		}
		dx = dx + 1;
	}
}

static void	render_minimap_column(t_engine *eng,
		int tile_x, int player_y, t_minimap *map)
{
	int	tile_y;
	int	half_tiles;

	half_tiles = 5;
	tile_y = player_y - half_tiles;
	if (tile_y < 0)
		tile_y = 0;
	while (tile_y <= player_y + half_tiles && tile_y < eng->map_h)
	{
		map->block_cell_x = tile_x;
		map->block_cell_y = tile_y;
		prepare_block(eng, map);
		draw_block_pixels(eng, map);
		tile_y = tile_y + 1;
	}
}

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
	while (tile_x <= player_x + 5 && tile_x < eng->map_w)
	{
		render_minimap_column(eng, tile_x, player_y, map);
		tile_x = tile_x + 1;
	}
}
