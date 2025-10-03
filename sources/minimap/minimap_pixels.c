/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 02:10:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/03 02:31:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <math.h>

static t_minimap_projection	minimap_project_pixel_to_tile(
		t_engine *engine, t_minimap *map, int pixel_x, int pixel_y)
{
	int						cx;
	double					right;
	double					forward;
	double					v;
	t_minimap_projection	out;

	cx = map->left + map->size / 2;
	right = (double)(pixel_x - cx) / (double)map->final_scale;
	forward = -(double)(pixel_y - (map->top + map->size / 2))
		/ (double)map->final_scale;
	v = engine->player.pos_x + (right * -engine->player.dir_y)
		+ (forward * engine->player.dir_x);
	out.tile_x = (int)floor(v);
	v = engine->player.pos_y + (right * engine->player.dir_x)
		+ (forward * engine->player.dir_y);
	out.tile_y = (int)floor(v);
	return (out);
}

void	render_minimap_pixels(t_engine *eng, t_minimap *map)
{
	int	x;
	int	y;

	if (!eng || !map)
		return ;
	x = map->left + 1;
	while (x < map->left + map->size - 1)
	{
		y = map->top + 1;
		while (y < map->top + map->size - 1)
		{
			minimap_compute_pixel_color(eng, map, x, y);
			mlx_put_pixel(eng->img.frame, x, y, map->block_color);
			y = y + 1;
		}
		x = x + 1;
	}
}

static int	compute_block_color_from_map(t_engine *engine, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= engine->map_w || my >= engine->map_h)
		return (MINIMAP_FOG_COLOR);
	if (engine->map[my][mx] == '1')
		return (MINIMAP_WALL_COLOR);
	if (engine->map[my][mx] == 'D')
		return (MINIMAP_DOOR_COLOR);
	if (engine->map[my][mx] == '0')
		return (MINIMAP_FLOOR_COLOR);
	return (MINIMAP_FOG_COLOR);
}

void	minimap_compute_pixel_color(t_engine *eng, t_minimap *map,
		int pixel_x, int pixel_y)
{
	int						color;
	t_minimap_projection	proj;

	if (!eng || !map)
		return ;
	proj = minimap_project_pixel_to_tile(eng, map, pixel_x, pixel_y);
	color = compute_block_color_from_map(eng, proj.tile_x, proj.tile_y);
	if (eng->explored_map && proj.tile_x >= 0 && proj.tile_y >= 0
		&& proj.tile_x < eng->map_w && proj.tile_y < eng->map_h
		&& !eng->explored_map[proj.tile_y][proj.tile_x])
		color = MINIMAP_FOG_COLOR;
	map->block_color = color;
}
