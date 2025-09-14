/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:00 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 18:41:31 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	note_player(t_map *map, int x, int y, int *found)
{
	if (*found)
		return (parser_error("multiple player positions"));
	map->player_x = x;
	map->player_y = y;
	map->player_dir = map->grid[y][x];
	map->grid[y][x] = '0';
	*found = 1;
	return (0);
}

int	locate_player(t_map *map)
{
	int	y;
	int	x;
	int	found;

	if (!map || !map->grid)
		return (parser_error("empty map"));
	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player(map->grid[y][x]))
			{
				if (note_player(map, x, y, &found) < 0)
					return (-1);
			}
			x++;
		}
		y++;
	}
	if (!found)
		return (parser_error("missing player position"));
	return (0);
}
