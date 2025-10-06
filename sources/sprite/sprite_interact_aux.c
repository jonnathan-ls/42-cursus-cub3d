/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"

/**
 * @brief Calculates Euclidean distance between sprite and player.
 *
 * @param eng Engine structure containing player position.
 * @param sprite Sprite to calculate distance to.
 * @return Distance between sprite and player.
 */
double	calc_distance(t_engine *eng, t_sprite *sprite)
{
	return (calc_euclidean_dist(sprite->x, sprite->y,
			eng->player.pos_x, eng->player.pos_y));
}

/**
 * @brief Checks if a sprite is an active enemy near the player.
 *
 * @param sprite Sprite to check.
 * @param eng Engine structure containing player position.
 * @return 1 if enemy is nearby and active, 0 otherwise.
 */
int	is_enemy_nearby(t_sprite *sprite, t_engine *eng)
{
	if (sprite->sprite_type != 1)
		return (0);
	if (sprite->collected || sprite->is_dying)
		return (0);
	return (calc_distance(eng, sprite) < 1.5);
}

/**
 * @brief Checks if any enemy sprite is near the player.
 *
 * @param eng Engine structure containing sprite list.
 * @return 1 if any enemy is nearby, 0 otherwise.
 */
int	has_nearby_enemy(t_engine *eng)
{
	int	i;

	i = 0;
	while (i < eng->sprites.count)
	{
		if (is_enemy_nearby(&eng->sprites.list[i], eng))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Handles coin collection and triggers victory condition.
 *
 * @param eng Engine structure containing game state.
 * @param sprite Coin sprite being collected.
 */
void	handle_coin_pickup(t_engine *eng, t_sprite *sprite)
{
	sprite->collected = 1;
	eng->player.game_over = 2;
}
