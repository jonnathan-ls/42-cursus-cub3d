/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 22:11:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <math.h>

static int	is_player_near_door(t_engine *eng, int door_x, int door_y)
{
	double	dist_x;
	double	dist_y;
	double	distance;

	dist_x = eng->player.pos_x - (double)door_x - 0.5;
	dist_y = eng->player.pos_y - (double)door_y - 0.5;
	distance = sqrt(dist_x * dist_x + dist_y * dist_y);
	return (distance <= 1.5);
}

static double	calculate_door_distance(t_engine *eng, int door_index)
{
	double	dist_x;
	double	dist_y;

	dist_x = eng->player.pos_x - (double)eng->doors.doors[door_index].x - 0.5;
	dist_y = eng->player.pos_y - (double)eng->doors.doors[door_index].y - 0.5;
	return (sqrt(dist_x * dist_x + dist_y * dist_y));
}

int	ft_find_nearest_door_index(t_engine *eng)
{
	int		i;
	int		nearest_index;
	double	min_distance;
	double	distance;

	if (!eng || !eng->doors.doors)
		return (-1);
	nearest_index = -1;
	min_distance = 2.0;
	i = 0;
	while (i < eng->doors.count)
	{
		if (is_player_near_door(eng, eng->doors.doors[i].x,
				eng->doors.doors[i].y))
		{
			distance = calculate_door_distance(eng, i);
			if (distance < min_distance)
			{
				min_distance = distance;
				nearest_index = i;
			}
		}
		i++;
	}
	return (nearest_index);
}
