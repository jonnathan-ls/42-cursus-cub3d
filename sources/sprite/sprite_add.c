/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:13:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"
#include "constants.h"

/**
 * @brief Finds the texture index for a given sprite type character.
 *
 * Searches through the sprite_chars array to locate the index matching
 * the provided type character.
 *
 * @param eng Engine structure containing sprite character mappings.
 * @param type Character representing the sprite type.
 * @return Index of the sprite type, or 0 if not found.
 */
static int	find_type_index(t_engine *eng, char type)
{
	int	i;

	if (!eng->sprite_chars)
		return (0);
	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (eng->sprite_chars[i] == type)
			return (i);
		i = i + 1;
	}
	return (0);
}

/**
 * @brief Initializes sprite position and default attribute values.
 *
 * Sets sprite world coordinates with center offset and initializes all
 * animation, health, and movement attributes to default values.
 *
 * @param sprite Sprite structure to initialize.
 * @param pos_x Grid X coordinate of the sprite.
 * @param pos_y Grid Y coordinate of the sprite.
 */
static void	set_sprite_position(t_sprite *sprite, int pos_x, int pos_y)
{
	sprite->x = (double)pos_x + SPRITE_CENTER_OFFSET;
	sprite->y = (double)pos_y + SPRITE_CENTER_OFFSET;
	sprite->distance = 0.0;
	sprite->collected = 0;
	sprite->current_frame = 0;
	sprite->anim_timer = 0.0;
	sprite->health = 0;
	sprite->is_dying = 0;
	sprite->death_timer = 0.0;
	sprite->move_dir_x = 0.0;
	sprite->move_dir_y = 0.0;
	sprite->move_timer = 0.0;
	sprite->move_speed = SPRITE_MOVE_SPEED;
}

/**
 * @brief Sets sprite type-specific data from configuration.
 *
 * Assigns sprite type, frame count, and health based on the sprite
 * configuration at the specified index.
 *
 * @param eng Engine structure containing sprite configurations.
 * @param sprite Sprite structure to configure.
 * @param index Configuration index for this sprite type.
 */
static void	set_sprite_type_data(t_engine *eng, t_sprite *sprite, int index)
{
	sprite->type_index = index;
	if (eng->sprites.sprite_types)
	{
		sprite->sprite_type = eng->sprites.sprite_types[index];
		if (sprite->sprite_type == SPRITE_TYPE_ENEMY)
			sprite->health = ENEMY_HEALTH;
	}
	else
		sprite->sprite_type = 0;
	if (eng->sprites.frame_counts)
		sprite->frame_count = eng->sprites.frame_counts[index];
	else
		sprite->frame_count = 1;
}

/**
 * @brief Adds a sprite to the sprite list at the current index.
 *
 * Finds the sprite type index, initializes position and type data, then
 * increments the index for the next sprite.
 *
 * @param eng Engine structure containing sprite list.
 * @param idx Pointer to current index in sprite list.
 * @param pos Array containing X and Y grid coordinates.
 * @param type Character representing the sprite type.
 */
void	add_sprite_to_list(t_engine *eng, int *idx, int pos[2], char type)
{
	int	type_index;

	type_index = find_type_index(eng, type);
	set_sprite_position(&eng->sprites.list[*idx], pos[0], pos[1]);
	set_sprite_type_data(eng, &eng->sprites.list[*idx], type_index);
	*idx = *idx + 1;
}
