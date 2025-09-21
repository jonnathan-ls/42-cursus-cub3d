/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/21 10:38:16 by jlacerda         ###   ########.fr       */
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
	return (distance <= 1.25);
}

int	ft_find_nearest_door_index(t_engine *eng)
{
	int	i;

	if (!eng || !eng->doors.list)
		return (-1);
	i = 0;
	while (i < eng->doors.count)
	{
		if (is_player_near_door(eng, eng->doors.list[i].x,
				eng->doors.list[i].y))
			return (i);
		i++;
	}
	return (-1);
}
