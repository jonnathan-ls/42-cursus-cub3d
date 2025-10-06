/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "constants.h"

double	calc_distance(t_engine *eng, t_sprite *sprite);
int		is_enemy_nearby(t_sprite *sprite, t_engine *eng);
int		has_nearby_enemy(t_engine *eng);

/**
 * @brief Applies damage to the player from enemy contact.
 *
 * Checks cooldown and health, decrements health, sets cooldown, and
 * triggers game over if health reaches zero.
 *
 * @param eng Engine structure containing player health and damage state.
 */
static void	apply_damage(t_engine *eng)
{
	eng->player.is_taking_damage = 1;
	if (eng->player.damage_cooldown > 0.0)
		return ;
	if (eng->player.health <= 0)
		return ;
	eng->player.health -= ENEMY_DAMAGE;
	eng->player.damage_cooldown = DAMAGE_COOLDOWN;
	if (eng->player.health <= 0)
	{
		eng->player.health = 0;
		eng->player.game_over = 1;
	}
}

/**
 * @brief Restores player health from health pickup.
 *
 * Increases player health by restoration amount, capping at maximum
 * health, and marks the sprite as collected.
 *
 * @param eng Engine structure containing player health.
 * @param sprite Health sprite being collected.
 */
static void	apply_health(t_engine *eng, t_sprite *sprite)
{
	if (eng->player.health >= MAX_HEALTH)
		return ;
	eng->player.health += HEALTH_RESTORE;
	if (eng->player.health > MAX_HEALTH)
		eng->player.health = MAX_HEALTH;
	sprite->collected = 1;
}

/**
 * @brief Processes interaction with a specific sprite.
 *
 * Determines sprite type and delegates to appropriate handler for
 * enemies, health pickups, or coin collection.
 *
 * @param eng Engine structure containing player state.
 * @param sprite Sprite being interacted with.
 */
static void	process_sprite(t_engine *eng, t_sprite *sprite)
{
	if (sprite->sprite_type == SPRITE_TYPE_ENEMY)
		apply_damage(eng);
	else if (sprite->sprite_type == SPRITE_TYPE_HEALTH)
		apply_health(eng, sprite);
	else if (sprite->sprite_type == SPRITE_TYPE_COIN)
		handle_coin_pickup(eng, sprite);
}

/**
 * @brief Checks for and processes sprite interactions each frame.
 *
 * Updates damage cooldown, checks for nearby enemies, and processes
 * interactions with sprites within interaction distance.
 *
 * @param param Engine structure cast from void pointer.
 */
void	check_sprite_interactions(void *param)
{
	t_engine	*eng;
	int			i;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list)
		return ;
	if (eng->player.damage_cooldown > 0.0)
		eng->player.damage_cooldown -= eng->mlx->delta_time;
	eng->player.is_taking_damage = has_nearby_enemy(eng);
	i = 0;
	while (i < eng->sprites.count)
	{
		if (!eng->sprites.list[i].collected)
		{
			if (calc_distance(eng, &eng->sprites.list[i])
				< SPRITE_INTERACT_DISTANCE)
				process_sprite(eng, &eng->sprites.list[i]);
		}
		i++;
	}
}
