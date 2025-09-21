/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/21 16:31:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include "cub3d.h"

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
	int	is_explored;

	dx = 0;
	if (!should_draw(eng->map[cell_y][cell_x], &color))
		return ;
	is_explored = 0;
	if (eng->explored_map && eng->explored_map[cell_y][cell_x])
		is_explored = 1;
	if (!is_explored)
		color = MINIMAP_FOG_COLOR;
	while (dx < scale)
	{
		dy = 0;
		while (dy < scale)
		{
			mlx_put_pixel(eng->img.frame, cell_x * scale + MINIMAP_OFFSET + dx,
				cell_y * scale + MINIMAP_OFFSET + dy, color);
			dy = dy + 1;
		}
		dx = dx + 1;
	}
}

int	ft_minimap_init_exploration(t_engine *eng)
{
	int	y;
	int	x;

	if (!eng)
		return (-1);
	eng->explored_map = mm_alloc(eng->map_h, sizeof(int *));
	if (!eng->explored_map)
		return (-1);
	y = 0;
	while (y < eng->map_h)
	{
		eng->explored_map[y] = mm_alloc(eng->map_w, sizeof(int));
		if (!eng->explored_map[y])
			return (-1);
		x = 0;
		while (x < eng->map_w)
		{
			eng->explored_map[y][x] = 0;
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_minimap_update_exploration(t_engine *eng)
{
	int		player_x;
	int		player_y;
	int		radius;
	int		dx;
	int		dy;

	if (!eng || !eng->explored_map)
		return ;
	player_x = (int)eng->player.pos_x;
	player_y = (int)eng->player.pos_y;
	radius = 2;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (player_x + dx >= 0 && player_x + dx < eng->map_w
				&& player_y + dy >= 0 && player_y + dy < eng->map_h)
				eng->explored_map[player_y + dy][player_x + dx] = 1;
			dx++;
		}
		dy++;
	}
}
