/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 22:19:02 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "shared.h"
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
				eng->doors.list[index].offset = 0.0;
				index++;
			}
			x++;
		}
		y++;
	}
}

int	config_doors(t_engine *eng)
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

void	handle_door_updates(t_engine *eng)
{
	int		i;
	double	speed;

	if (!eng || !eng->doors.list)
		return ;
	i = 0;
	speed = 4.0 * eng->mlx->delta_time;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].is_open)
		{
			if (eng->doors.list[i].offset < 1.0)
				eng->doors.list[i].offset += speed;
			if (eng->doors.list[i].offset > 1.0)
				eng->doors.list[i].offset = 1.0;
		}
		else
		{
			if (eng->doors.list[i].offset > 0.0)
				eng->doors.list[i].offset -= speed;
			if (eng->doors.list[i].offset < 0.0)
				eng->doors.list[i].offset = 0.0;
		}
		i++;
	}
}

int	get_door_texture_offset(t_engine *eng, int map_x, int map_y)
{
	int	i;
	int	cell_w;

	if (!eng || !eng->doors.list)
		return (0);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].x == map_x && eng->doors.list[i].y == map_y)
		{
			cell_w = eng->win_w / eng->map_w;
			return ((int)(eng->doors.list[i].offset * (double)cell_w));
		}
		i++;
	}
	return (0);
}
