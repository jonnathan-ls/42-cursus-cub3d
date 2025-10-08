/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/07 23:54:06 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include "shared.h"
#include <MLX42/MLX42.h>

/**
 * @brief Draws the border frame around the minimap.
 *
 * Renders the top, bottom, left, and right edges of the minimap square
 * using the wall color to create a visible border.
 *
 * @param eng Engine structure containing frame buffer.
 * @param info Minimap drawing information with position and size.
 */
void	draw_minimap_frame(t_engine *eng, t_map_draw_info *info)
{
	int	i;
	int	end;

	if (!eng || !eng->frame || !info)
		return ;
	end = info->left + info->size - TEXTURE_CLAMP_ONE;
	i = 0;
	while (i < info->size)
	{
		mlx_put_pixel(eng->frame, info->left + i, info->top,
			MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->frame, info->left + i, info->top + info->size
			- TEXTURE_CLAMP_ONE, MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->frame, info->left, info->top + i,
			MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->frame, end, info->top + i, MINIMAP_WALL_COLOR);
		i = i + 1;
	}
}

/**
 * @brief Fills the minimap background with fog color.
 *
 * Draws the entire interior of the minimap with the fog color, which
 * will be overwritten by actual map data during rendering.
 *
 * @param eng Engine structure containing frame buffer.
 * @param map Minimap structure with position and size information.
 */
void	draw_minimap_background(t_engine *eng, t_minimap *map)
{
	int	x;
	int	y;
	int	end;

	if (!eng || !map || !eng->frame)
		return ;
	end = map->left + map->size - TEXTURE_CLAMP_ONE;
	x = map->left + TEXTURE_CLAMP_ONE;
	while (x < end)
	{
		y = map->top + TEXTURE_CLAMP_ONE;
		while (y < map->top + map->size - TEXTURE_CLAMP_ONE)
		{
			mlx_put_pixel(eng->frame, x, y, MINIMAP_FOG_COLOR);
			y = y + 1;
		}
		x = x + 1;
	}
}
