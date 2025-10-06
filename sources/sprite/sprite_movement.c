/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"
#include "constants.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief Checks if a map tile is walkable for enemy sprites.
 *
 * @param eng Engine structure containing map data.
 * @param map_x X coordinate of tile.
 * @param map_y Y coordinate of tile.
 * @return 1 if walkable, 0 otherwise.
 */
static int	check_map_tile(t_engine *eng, int map_x, int map_y)
{
	return (is_walkable_tile(eng, map_x, map_y));
}

/**
 * @brief Validates if position is walkable including collision margin.
 *
 * @param eng Engine structure containing map data.
 * @param x X coordinate to validate.
 * @param y Y coordinate to validate.
 * @return 1 if position is valid, 0 otherwise.
 */
static int	is_valid_position(t_engine *eng, double x, double y)
{
	double	margin;

	margin = 0.3;
	if (!check_map_tile(eng, (int)x, (int)y))
		return (0);
	if (!check_map_tile(eng, (int)(x - margin), (int)y))
		return (0);
	if (!check_map_tile(eng, (int)(x + margin), (int)y))
		return (0);
	if (!check_map_tile(eng, (int)x, (int)(y - margin)))
		return (0);
	if (!check_map_tile(eng, (int)x, (int)(y + margin)))
		return (0);
	return (1);
}

/**
 * @brief Sets a random movement direction for an enemy sprite.
 *
 * @param sprite Sprite to set direction for.
 */
static void	set_random_direction(t_sprite *sprite)
{
	int		direction;
	double	angle;

	direction = rand() % 8;
	angle = direction * 0.785398;
	sprite->move_dir_x = cos(angle);
	sprite->move_dir_y = sin(angle);
	sprite->move_timer = 2.0 + (rand() % 3);
}

/**
 * @brief Updates enemy sprite position with collision detection.
 *
 * @param eng Engine structure containing map data.
 * @param sprite Enemy sprite to update.
 * @param dt Delta time for frame-independent movement.
 */
static void	update_enemy_position(t_engine *eng, t_sprite *sprite, double dt)
{
	double	new_x;
	double	new_y;

	if (sprite->move_timer <= 0.0)
	{
		set_random_direction(sprite);
		return ;
	}
	new_x = sprite->x + sprite->move_dir_x * sprite->move_speed * dt;
	new_y = sprite->y + sprite->move_dir_y * sprite->move_speed * dt;
	if (is_valid_position(eng, new_x, sprite->y))
		sprite->x = new_x;
	else
		sprite->move_timer = 0.0;
	if (is_valid_position(eng, sprite->x, new_y))
		sprite->y = new_y;
	else
		sprite->move_timer = 0.0;
	sprite->move_timer -= dt;
}

/**
 * @brief Updates movement for all enemy sprites each frame.
 *
 * @param param Engine structure cast from void pointer.
 * @param delta Delta time for frame-independent movement.
 */
void	update_enemy_movement(void *param, double delta)
{
	t_engine	*eng;
	int			i;
	t_sprite	*sprite;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list)
		return ;
	i = 0;
	while (i < eng->sprites.count)
	{
		sprite = &eng->sprites.list[i];
		if (sprite->sprite_type == SPRITE_TYPE_ENEMY)
		{
			if (!sprite->collected && !sprite->is_dying)
				update_enemy_position(eng, sprite, delta);
		}
		i++;
	}
}
