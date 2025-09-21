/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/21 10:56:48 by jlacerda         ###   ########.fr       */
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
				eng->doors.list[index].x = x;
				eng->doors.list[index].y = y;
				eng->doors.list[index].is_open = 0;
				index++;
			}
			x++;
		}
		y++;
	}
}

int	ft_doors_init(t_engine *eng)
{
	int	doors_count;

	if (!eng)
		return (-1);
	doors_count = count_doors_in_map(eng);
	eng->doors.count = doors_count;
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
