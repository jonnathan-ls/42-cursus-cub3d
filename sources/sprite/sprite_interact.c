/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 13:48:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include <math.h>

static double	calculate_distance(t_engine *eng, t_sprite *sprite)
{
	double	dx;
	double	dy;

	dx = sprite->x - eng->player.pos_x;
	dy = sprite->y - eng->player.pos_y;
	return (sqrt(dx * dx + dy * dy));
}

static void	handle_enemy_damage(t_engine *eng)
{
	if (eng->player.damage_cooldown > 0.0)
		return ;
	if (eng->player.health > 0)
	{
		eng->player.health = eng->player.health - 10;
		eng->player.damage_cooldown = 1.0;
		if (eng->player.health <= 0)
		{
			eng->player.health = 0;
			eng->player.game_over = 1;
		}
	}
}

static void	handle_health_pickup(t_engine *eng, t_sprite *sprite)
{
	if (eng->player.health < 100)
	{
		eng->player.health = eng->player.health + 25;
		if (eng->player.health > 100)
			eng->player.health = 100;
	}
	sprite->collected = 1;
}

static void	process_interaction(t_engine *eng, t_sprite *sprite)
{
	if (sprite->sprite_type == 1)
		handle_enemy_damage(eng);
	else if (sprite->sprite_type == 2)
		handle_health_pickup(eng, sprite);
	else if (sprite->sprite_type == 3)
		handle_coin_pickup(eng, sprite);
}

void	check_sprite_interactions(void *param)
{
	t_engine	*eng;
	int			i;
	double		dist;
	double		cooldown;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list)
		return ;
	cooldown = eng->player.damage_cooldown - eng->mlx->delta_time;
	if (eng->player.damage_cooldown > 0.0)
		eng->player.damage_cooldown = cooldown;
	i = 0;
	while (i < eng->sprites.count)
	{
		if (eng->sprites.list[i].collected == 0)
		{
			dist = calculate_distance(eng, &eng->sprites.list[i]);
			if (dist < 0.8)
				process_interaction(eng, &eng->sprites.list[i]);
		}
		i = i + 1;
	}
}
