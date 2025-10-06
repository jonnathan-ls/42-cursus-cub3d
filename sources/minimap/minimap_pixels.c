/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 02:10:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include "shared.h"
#include <math.h>

static t_minimap_projection	project_pixel_to_tile(t_engine *engine,
		t_minimap *map, int pixel_x, int pixel_y)
{
	int						center_x;
	double					right;
	double					forward;
	double					value;
	t_minimap_projection	out;

	center_x = map->left + map->size / CENTER_FACTOR;
	right = (double)(pixel_x - center_x) / (double)map->final_scale;
	forward = -(double)(pixel_y - (map->top + map->size / CENTER_FACTOR))
		/ (double)map->final_scale;
	value = engine->player.pos_x + (right * -engine->player.dir_y)
		+ (forward * engine->player.dir_x);
	out.tile_x = (int)floor(value);
	value = engine->player.pos_y + (right * engine->player.dir_x)
		+ (forward * engine->player.dir_y);
	out.tile_y = (int)floor(value);
	return (out);
}

void	render_minimap_pixels(t_engine *eng, t_minimap *map)
{
	int	pixel_x;
	int	pixel_y;

	if (!eng || !map)
		return ;
	pixel_x = map->left + TEXTURE_CLAMP_ONE;
	while (pixel_x < map->left + map->size - TEXTURE_CLAMP_ONE)
	{
		pixel_y = map->top + TEXTURE_CLAMP_ONE;
		while (pixel_y < map->top + map->size - TEXTURE_CLAMP_ONE)
		{
			compute_minimap_pixel_color(eng, map, pixel_x, pixel_y);
			mlx_put_pixel(eng->frame, pixel_x, pixel_y, map->block_color);
			pixel_y = pixel_y + 1;
		}
		pixel_x = pixel_x + 1;
	}
}

static int	compute_block_color_from_map(t_engine *engine, int mx, int my)
{
	if (!is_valid_map_coords(engine, mx, my))
		return (MINIMAP_EXTERNAL_COLOR);
	if (engine->map[my][mx] == '1')
		return (MINIMAP_WALL_COLOR);
	if (engine->map[my][mx] == 'D')
		return (MINIMAP_DOOR_COLOR);
	if (engine->map[my][mx] == '0')
		return (MINIMAP_FLOOR_COLOR);
	return (MINIMAP_FOG_COLOR);
}

void	compute_minimap_pixel_color(t_engine *eng, t_minimap *map,
	int pixel_x, int pixel_y)
{
	t_minimap_projection	proj;

	if (!eng || !map)
		return ;
	proj = project_pixel_to_tile(eng, map, pixel_x, pixel_y);
	if (!is_valid_map_coords(eng, proj.tile_x, proj.tile_y))
	{
		map->block_color = MINIMAP_EXTERNAL_COLOR;
		return ;
	}
	map->block_color = compute_block_color_from_map(eng,
			proj.tile_x, proj.tile_y);
}
