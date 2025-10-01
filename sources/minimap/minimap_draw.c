/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/03 00:22:14 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>

void	draw_minimap_frame(t_engine *eng, int left, int top, int size)
{
	int	i;
	int	end;

	if (!eng || !eng->img.frame)
		return ;
	end = left + size - 1;
	i = 0;
	while (i < size)
	{
		mlx_put_pixel(eng->img.frame, left + i, top, MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->img.frame, left + i, top + size - 1,
			MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->img.frame, left, top + i, MINIMAP_WALL_COLOR);
		mlx_put_pixel(eng->img.frame, end, top + i, MINIMAP_WALL_COLOR);
		i = i + 1;
	}
}

void	draw_background_minimap(t_engine *eng, t_minimap *map)
{
	int	x;
	int	y;
	int	end;

	if (!eng || !map || !eng->img.frame)
		return ;
	end = map->left + map->size - 1;
	x = map->left + 1;
	while (x < end)
	{
		y = map->top + 1;
		while (y < map->top + map->size - 1)
		{
			mlx_put_pixel(eng->img.frame, x, y, MINIMAP_FOG_COLOR);
			y = y + 1;
		}
		x = x + 1;
	}
}
