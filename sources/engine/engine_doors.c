/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/15 20:35:35 by peda-cos         ###   ########.fr       */
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
 * Initializes a single map cell entry inside the doors grid.
 * @param eng Pointer to engine structure.
 * @param x X coordinate inside the map.
 * @param y Y coordinate inside the map.
 * @param index Pointer to the running door index.
 */
static void	init_door_cell(t_engine *eng, int x, int y, int *index)
{
	eng->doors.grid[y][x] = -1;
	if (eng->map[y][x] != 'D')
		return ;
	eng->doors.list[*index].x = x;
	eng->doors.list[*index].y = y;
	eng->doors.list[*index].is_open = 0;
	eng->doors.list[*index].is_active = 1;
	eng->doors.list[*index].offset = 0.0;
	eng->doors.grid[y][x] = *index;
	*index = *index + 1;
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
			init_door_cell(eng, x, y, &index);
			x = x + 1;
		}
		y = y + 1;
	}
}

/**
 * Allocates 2D grid for door lookup.
 * @param eng Pointer to engine structure.
 * @return 0 on success, -1 on failure.
 */
static int	allocate_door_grid(t_engine *eng)
{
	int	y;

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
	return (0);
}

/**
 * Initializes door system from map data.
 * @param eng Pointer to engine structure.
 * @return 0 on success, -1 on failure.
 */
int	configure_doors(t_engine *eng)
{
	int	doors_count;

	if (!eng)
		return (-1);
	doors_count = count_doors_in_map(eng);
	eng->doors.count = doors_count;
	if (allocate_door_grid(eng) < 0)
		return (-1);
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
