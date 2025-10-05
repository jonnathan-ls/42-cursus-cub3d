/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:04 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 10:52:35 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_sprite_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == 'D')
		return (1);
	if (is_sprite_char(c))
		return (1);
	return (0);
}

int	validate_map_chars(t_map *map)
{
	int	y;
	int	x;

	if (!map || !map->grid)
		return (parser_error("empty map"));
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!is_valid_char(map->grid[y][x]))
				return (parser_error("invalid map character"));
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}
