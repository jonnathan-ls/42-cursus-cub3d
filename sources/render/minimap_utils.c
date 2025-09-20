/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/20 16:15:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"

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
	if (eng->map[cell_y][cell_x] == '1')
		color = MINIMAP_WALL_COLOR;
	else
		color = MINIMAP_FLOOR_COLOR;
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

int	ft_minimap_init(t_engine *eng)
{
	if (!eng)
		return (-1);
	eng->minimap_visible = 1;
	eng->minimap_scale = MINIMAP_MIN_SCALE;
	eng->minimap_toggle_prev = 0;
	return (0);
}

void	ft_minimap_toggle(t_engine *eng, int pressed, int *key_prev)
{
	if (!eng || !key_prev)
		return ;
	if (pressed && !(*key_prev))
		eng->minimap_visible = !eng->minimap_visible;
	*key_prev = pressed;
}
