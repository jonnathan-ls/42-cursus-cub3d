/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:25:14 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "constants.h"

double	calc_distance(t_engine *eng, t_sprite *sprite);
int		is_enemy_nearby(t_sprite *sprite, t_engine *eng);
int		has_nearby_enemy(t_engine *eng);

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

static void	apply_health(t_engine *eng, t_sprite *sprite)
{
	if (eng->player.health >= MAX_HEALTH)
		return ;
	eng->player.health += HEALTH_RESTORE;
	if (eng->player.health > MAX_HEALTH)
		eng->player.health = MAX_HEALTH;
	sprite->collected = 1;
}

static void	process_sprite(t_engine *eng, t_sprite *sprite)
{
	if (sprite->sprite_type == SPRITE_TYPE_ENEMY)
		apply_damage(eng);
	else if (sprite->sprite_type == SPRITE_TYPE_HEALTH)
		apply_health(eng, sprite);
	else if (sprite->sprite_type == SPRITE_TYPE_COIN)
		handle_coin_pickup(eng, sprite);
}

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
