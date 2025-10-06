/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:13:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"

/**
 * @brief Checks if a character represents a valid sprite.
 *
 * Returns true for uppercase letters except 'D' (reserved for doors).
 *
 * @param c Character to check.
 * @return 1 if character is a sprite, 0 otherwise.
 */
static int	is_sprite_char(char c)
{
	if (c == 'D')
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

/**
 * @brief Counts total number of sprites in the map.
 *
 * Iterates through the entire map grid, counting cells that contain
 * valid sprite characters.
 *
 * @param eng Engine structure containing map data.
 * @return Total count of sprites in the map.
 */
int	count_sprites_in_map(t_engine *eng)
{
	int	count;
	int	pos_y;
	int	pos_x;

	count = 0;
	pos_y = 0;
	while (pos_y < eng->map_height)
	{
		pos_x = 0;
		while (pos_x < eng->map_width)
		{
			if (is_sprite_char(eng->map[pos_y][pos_x]))
				count = count + 1;
			pos_x = pos_x + 1;
		}
		pos_y = pos_y + 1;
	}
	return (count);
}

/**
 * @brief Allocates memory for sprite list and order array.
 *
 * Creates arrays to store sprite data and rendering order based on
 * the sprite count.
 *
 * @param eng Engine structure to allocate sprite arrays in.
 * @return 0 on success, -1 on allocation failure.
 */
int	allocate_sprites(t_engine *eng)
{
	eng->sprites.list = mm_alloc(eng->sprites.count, sizeof(t_sprite));
	if (!eng->sprites.list)
		return (-1);
	eng->sprites.order = mm_alloc(eng->sprites.count, sizeof(int));
	if (!eng->sprites.order)
		return (-1);
	return (0);
}

/**
 * @brief Populates sprite list from map data.
 *
 * Iterates through the map, adding each sprite character to the sprite
 * list with its position and type.
 *
 * @param eng Engine structure containing map and sprite list.
 */
void	fill_sprites(t_engine *eng)
{
	int		pos[3];
	char	cell;

	pos[2] = 0;
	pos[1] = 0;
	while (pos[1] < eng->map_height)
	{
		pos[0] = 0;
		while (pos[0] < eng->map_width)
		{
			cell = eng->map[pos[1]][pos[0]];
			if (is_sprite_char(cell))
				add_sprite_to_list(eng, &pos[2], pos, cell);
			pos[0] = pos[0] + 1;
		}
		pos[1] = pos[1] + 1;
	}
}

/**
 * @brief Collects all sprites from the map into the sprite system.
 *
 * Counts sprites in the map, allocates necessary arrays, and populates
 * the sprite list with position and type data.
 *
 * @param param Engine structure cast from void pointer.
 * @return 0 on success, -1 on failure.
 */
int	collect_sprites_from_map(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng || !eng->map)
		return (-1);
	if (eng->sprites.texture_count == 0)
		return (0);
	eng->sprites.count = count_sprites_in_map(eng);
	if (eng->sprites.count == 0)
		return (0);
	if (allocate_sprites(eng) != 0)
		return (-1);
	fill_sprites(eng);
	return (0);
}
