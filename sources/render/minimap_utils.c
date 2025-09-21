/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/21 15:55:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"

static int	should_draw(char cell, int *color)
{
	if (cell == '1')
	{
		*color = MINIMAP_WALL_COLOR;
		return (1);
	}
	else if (cell == 'D')
	{
		*color = MINIMAP_DOOR_COLOR;
		return (1);
	}
	else if (cell == '0')
	{
		*color = MINIMAP_FLOOR_COLOR;
		return (1);
	}
	return (0);
}

void	ft_minimap_render_cells(t_engine *eng, int final_scale)
{
	int	cell_x;
	int	cell_y;

	cell_x = 0;
	while (cell_x < eng->map_w)
	{
		cell_y = 0;
		while (cell_y < eng->map_h)
		{
			ft_minimap_draw_cell_block(eng, cell_x, cell_y, final_scale);
			cell_y = cell_y + 1;
		}
		cell_x = cell_x + 1;
	}
}

void	ft_minimap_draw_cell_block(
	t_engine *eng, int cell_x, int cell_y, int scale)
{
	int	dx;
	int	dy;
	int	color;

	dx = 0;
	if (!should_draw(eng->map[cell_y][cell_x], &color))
		return ;
	while (dx < scale)
	{
		dy = 0;
		while (dy < scale)
		{
			mlx_put_pixel(eng->img.frame,
				cell_x * scale + MINIMAP_OFFSET + dx,
				cell_y * scale + MINIMAP_OFFSET + dy,
				color);
			dy = dy + 1;
		}
		dx = dx + 1;
	}
}

void	ft_minimap_init(t_engine *eng)
{
	if (!eng)
		return ;
	eng->minimap_scale = 3;
	eng->minimap_visible = 1;
	eng->minimap_toggle_prev = 0;
}
