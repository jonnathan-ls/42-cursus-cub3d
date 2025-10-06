/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:25:59 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"

double	calc_distance(t_engine *eng, t_sprite *sprite)
{
	return (calc_euclidean_dist(sprite->x, sprite->y,
			eng->player.pos_x, eng->player.pos_y));
}

int	is_enemy_nearby(t_sprite *sprite, t_engine *eng)
{
	if (sprite->sprite_type != 1)
		return (0);
	if (sprite->collected || sprite->is_dying)
		return (0);
	return (calc_distance(eng, sprite) < 1.5);
}

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

void	handle_coin_pickup(t_engine *eng, t_sprite *sprite)
{
	sprite->collected = 1;
	eng->player.game_over = 2;
}
