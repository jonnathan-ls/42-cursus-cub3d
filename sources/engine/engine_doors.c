/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 22:27:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "cub3d.h"
#include <MLX42/MLX42.h>

static int	count_doors_in_map(t_engine *eng)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < eng->map_h)
	{
		x = 0;
		while (x < eng->map_w)
		{
			if (eng->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	fill_doors_array(t_engine *eng)
{
	int	index;
	int	y;
	int	x;

	index = 0;
	y = 0;
	while (y < eng->map_h)
	{
		x = 0;
		while (x < eng->map_w)
		{
			if (eng->map[y][x] == 'D')
			{
				eng->doors.doors[index].x = x;
				eng->doors.doors[index].y = y;
				eng->doors.doors[index].is_open = 0;
				index++;
			}
			x++;
		}
		y++;
	}
}

int	ft_doors_init(t_engine *eng)
{
	int	door_count;

	if (!eng)
		return (-1);
	door_count = count_doors_in_map(eng);
	eng->doors.count = door_count;
	if (door_count == 0)
	{
		eng->doors.doors = NULL;
		return (0);
	}
	eng->doors.doors = mm_alloc(door_count, sizeof(t_door));
	if (!eng->doors.doors)
		return (-1);
	fill_doors_array(eng);
	return (0);
}
