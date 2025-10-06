/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:16:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "shared.h"

int	find_nearest_door_index(t_engine *eng)
{
	int		i;
	double	door_x;
	double	door_y;

	if (!eng || !eng->doors.list)
		return (-1);
	i = 0;
	while (i < eng->doors.count)
	{
		door_x = (double)eng->doors.list[i].x + 0.5;
		door_y = (double)eng->doors.list[i].y + 0.5;
		if (is_in_radius(eng->player.pos_x, eng->player.pos_y,
				door_x, door_y))
			return (i);
		i = i + 1;
	}
	return (-1);
}
