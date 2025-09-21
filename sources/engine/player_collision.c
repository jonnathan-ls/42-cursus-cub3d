/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 22:10:56 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>

static int	is_wall_at(t_engine *eng, double x, double y)
{
	int	map_x;
	int	map_y;

	if (!eng || !eng->map)
		return (1);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= eng->map_w || map_y < 0 || map_y >= eng->map_h)
		return (1);
	if (!eng->map[map_y] || !eng->map[map_y][map_x])
		return (1);
	if (eng->map[map_y][map_x] == '1')
		return (1);
	if (eng->map[map_y][map_x] == 'D')
	{
		if (ft_is_door_open_at(eng, map_x, map_y))
			return (0);
		return (1);
	}
	return (0);
}

int	ft_check_collision_with_buffer(t_engine *eng, double x, double y)
{
	double	buffer;

	buffer = 0.15;
	if (is_wall_at(eng, x - buffer, y) || is_wall_at(eng, x + buffer, y))
		return (1);
	if (is_wall_at(eng, x, y - buffer) || is_wall_at(eng, x, y + buffer))
		return (1);
	if (is_wall_at(eng, x - buffer, y - buffer))
		return (1);
	if (is_wall_at(eng, x + buffer, y + buffer))
		return (1);
	return (0);
}
