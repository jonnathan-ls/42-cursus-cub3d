/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_exploration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:40:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/03 02:31:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include <stdlib.h>

int	allocate_explored_map(t_engine *eng)
{
	int	y;

	eng->explored_map = malloc(sizeof(int *) * eng->map_h);
	if (!eng->explored_map)
		return (0);
	y = 0;
	while (y < eng->map_h)
	{
		eng->explored_map[y] = malloc(sizeof(int) * eng->map_w);
		if (!eng->explored_map[y])
			return (0);
		y = y + 1;
	}
	return (1);
}

int	initialize_minimap_exploration(t_engine *eng)
{
	int	x;
	int	y;

	if (!eng)
		return (0);
	if (!allocate_explored_map(eng))
		return (0);
	y = 0;
	while (y < eng->map_h)
	{
		x = 0;
		while (x < eng->map_w)
		{
			eng->explored_map[y][x] = 0;
			x = x + 1;
		}
		y = y + 1;
	}
	return (1);
}

void	handle_minimap_exploration(t_engine *eng)
{
	int	px;
	int	py;

	if (!eng || !eng->explored_map)
		return ;
	px = (int)eng->player.pos_x;
	py = (int)eng->player.pos_y;
	if (px >= 0 && px < eng->map_w && py >= 0 && py < eng->map_h)
		eng->explored_map[py][px] = 1;
}
