/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <math.h>

int	find_nearest_door_index(t_engine *eng)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;

	if (!eng || !eng->doors.list)
		return (-1);
	i = 0;
	while (i < eng->doors.count)
	{
		dx = eng->player.pos_x - (double)eng->doors.list[i].x - 0.5;
		dy = eng->player.pos_y - (double)eng->doors.list[i].y - 0.5;
		dist = sqrt(dx * dx + dy * dy);
		if (dist <= 1.75)
			return (i);
		i++;
	}
	return (-1);
}
