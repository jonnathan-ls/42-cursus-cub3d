/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:13:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "constants.h"

/**
 * @brief Finds the texture index for enemy death animation.
 *
 * Searches sprite configurations for the SPRITE_TYPE_ENEMY_DEAD type.
 *
 * @param eng Engine structure containing sprite configurations.
 * @return Index of death texture, or -1 if not found.
 */
int	get_death_texture_index(t_engine *eng)
{
	int	i;

	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (eng->sprites.configs[i].type == SPRITE_TYPE_ENEMY_DEAD)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Retrieves the appropriate texture for a sprite.
 *
 * Returns death texture if sprite is dying, otherwise returns the
 * sprite's normal texture.
 *
 * @param eng Engine structure containing sprite textures.
 * @param sprite Sprite to get texture for.
 * @return Pointer to the appropriate texture.
 */
mlx_texture_t	*get_sprite_texture(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (eng->sprites.textures[sprite->type_index]);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (eng->sprites.textures[sprite->type_index]);
	return (eng->sprites.textures[death_idx]);
}

/**
 * @brief Retrieves the frame count for a sprite's current state.
 *
 * Returns death animation frame count if sprite is dying, otherwise
 * returns the sprite's normal frame count.
 *
 * @param eng Engine structure containing sprite configurations.
 * @param sprite Sprite to get frame count for.
 * @return Number of animation frames.
 */
int	get_sprite_frame_count(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (sprite->frame_count);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (sprite->frame_count);
	return (eng->sprites.configs[death_idx].frames);
}

/**
 * @brief Retrieves the texture index for a sprite's current state.
 *
 * Returns death texture index if sprite is dying, otherwise returns
 * the sprite's normal texture index.
 *
 * @param eng Engine structure containing sprite configurations.
 * @param sprite Sprite to get texture index for.
 * @return Index of the appropriate texture.
 */
int	get_sprite_texture_index(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (sprite->type_index);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (sprite->type_index);
	return (death_idx);
}
