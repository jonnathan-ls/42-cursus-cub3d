/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 03:09:07 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "shared.h"
#include "constants.h"
#include <MLX42/MLX42.h>

/**
 * Counts total number of doors in the map.
 * @param eng Pointer to engine structure.
 * @return Number of doors found.
 */
static int	count_doors_in_map(t_engine *eng)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < eng->map_height)
	{
		x = 0;
		while (x < eng->map_width)
		{
			if (eng->map[y][x] == 'D')
				count = count + 1;
			x = x + 1;
		}
		y = y + 1;
	}
	return (count);
}

/**
 * Populates doors array with positions from map.
 * @param eng Pointer to engine structure.
 */
static void	fill_doors_array(t_engine *eng)
{
	int	index;
	int	y;
	int	x;

	index = 0;
	y = 0;
	while (y < eng->map_height)
	{
		x = 0;
		while (x < eng->map_width)
		{
			eng->doors.grid[y][x] = -1;
			if (eng->map[y][x] == 'D')
			{
				eng->doors.list[index].x = x;
				eng->doors.list[index].y = y;
				eng->doors.list[index].is_open = 0;
				eng->doors.list[index].offset = 0.0;
				eng->doors.grid[y][x] = index;
				index = index + 1;
			}
			x = x + 1;
		}
		y = y + 1;
	}
}

/**
 * Initializes door system from map data.
 * @param eng Pointer to engine structure.
 * @return 0 on success, -1 on failure.
 */
int	configure_doors(t_engine *eng)
{
	int	doors_count;
	int	y;

	if (!eng)
		return (-1);
	doors_count = count_doors_in_map(eng);
	eng->doors.count = doors_count;
	eng->doors.grid = mm_alloc(eng->map_height, sizeof(int *));
	if (!eng->doors.grid)
		return (-1);
	y = 0;
	while (y < eng->map_height)
	{
		eng->doors.grid[y] = mm_alloc(eng->map_width, sizeof(int));
		if (!eng->doors.grid[y])
			return (-1);
		y = y + 1;
	}
	if (doors_count == 0)
	{
		eng->doors.list = NULL;
		return (0);
	}
	eng->doors.list = mm_alloc(doors_count, sizeof(t_door));
	if (!eng->doors.list)
		return (-1);
	fill_doors_array(eng);
	return (0);
}

/**
 * Updates door animation offsets for opening and closing.
 * @param eng Pointer to engine structure.
 */
void	handle_door_updates(t_engine *eng)
{
	int		i;
	double	speed;

	if (!eng || !eng->doors.list)
		return ;
	i = 0;
	speed = DOOR_ANIM_SPEED * eng->mlx->delta_time;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].is_open && eng->doors.list[i].offset < 1.0)
		{
			eng->doors.list[i].offset = eng->doors.list[i].offset + speed;
			if (eng->doors.list[i].offset > 1.0)
				eng->doors.list[i].offset = 1.0;
		}
		if (!eng->doors.list[i].is_open && eng->doors.list[i].offset > 0.0)
		{
			eng->doors.list[i].offset = eng->doors.list[i].offset - speed;
			if (eng->doors.list[i].offset < 0.0)
				eng->doors.list[i].offset = 0.0;
		}
		i = i + 1;
	}
}

/**
 * Gets texture offset for animated door at position.
 * @param eng Pointer to engine structure.
 * @param map_x X coordinate of door.
 * @param map_y Y coordinate of door.
 * @return Texture offset in pixels.
 */
int	get_door_texture_offset(t_engine *eng, int map_x, int map_y)
{
	int	door_idx;
	int	cell_w;

	if (!eng || !eng->doors.list || !eng->doors.grid)
		return (0);
	if (map_y < 0 || map_y >= eng->map_height)
		return (0);
	if (map_x < 0 || map_x >= eng->map_width)
		return (0);
	door_idx = eng->doors.grid[map_y][map_x];
	if (door_idx < 0 || door_idx >= eng->doors.count)
		return (0);
	cell_w = eng->window_width / eng->map_width;
	return ((int)(eng->doors.list[door_idx].offset * (double)cell_w));
}
