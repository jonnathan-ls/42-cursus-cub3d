/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:39:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "shared.h"
#include "constants.h"

/**
 * Finds nearest door within interaction radius.
 * @param eng Pointer to engine structure.
 * @return Door index or -1 if none found.
 */
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
		door_x = (double)eng->doors.list[i].x + DOOR_CENTER_OFFSET;
		door_y = (double)eng->doors.list[i].y + DOOR_CENTER_OFFSET;
		if (is_in_radius(eng->player.pos_x, eng->player.pos_y,
				door_x, door_y))
			return (i);
		i = i + 1;
	}
	return (-1);
}
