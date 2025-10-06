/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:12:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	is_valid_map_coords(t_engine *eng, int map_x, int map_y)
{
	if (!eng || !eng->map)
		return (0);
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_x >= eng->map_width)
		return (0);
	if (map_y >= eng->map_height)
		return (0);
	return (1);
}

int	is_walkable_tile(t_engine *eng, int map_x, int map_y)
{
	if (!is_valid_map_coords(eng, map_x, map_y))
		return (0);
	if (eng->map[map_y][map_x] == '1')
		return (0);
	if (eng->map[map_y][map_x] == 'D')
		return (0);
	return (1);
}

char	get_map_tile(t_engine *eng, int map_x, int map_y)
{
	if (!is_valid_map_coords(eng, map_x, map_y))
		return ('1');
	return (eng->map[map_y][map_x]);
}
