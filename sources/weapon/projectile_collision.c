/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:02:59 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"
#include "shared.h"

static void	apply_damage_to_sprite(t_sprite *sprite, int damage)
{
	if (sprite->health <= 0 || sprite->is_dying)
		return ;
	sprite->health = sprite->health - damage;
	if (sprite->health <= 0)
	{
		sprite->health = 0;
		sprite->is_dying = 1;
		sprite->death_timer = 0.0;
		sprite->current_frame = 0;
	}
}

static void	check_projectile_sprite_hit(t_engine *eng,
	t_projectile *proj, int i)
{
	double	dist;

	if (eng->sprites.list[i].sprite_type != 1)
		return ;
	if (eng->sprites.list[i].collected == 1)
		return ;
	if (eng->sprites.list[i].is_dying == 1)
		return ;
	dist = calc_euclidean_dist(proj->x, proj->y,
			eng->sprites.list[i].x, eng->sprites.list[i].y);
	if (dist < 0.5)
	{
		apply_damage_to_sprite(&eng->sprites.list[i], proj->damage);
		proj->active = 0;
	}
}

int	is_wall(t_engine *eng, double x, double y)
{
	return (!is_walkable_tile(eng, (int)x, (int)y));
}

void	check_projectile_hits(void *param)
{
	t_engine	*eng;
	int			i;
	int			j;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (eng->weapon.projectiles[i].active)
		{
			j = 0;
			while (j < eng->sprites.count)
			{
				check_projectile_sprite_hit(
					eng, &eng->weapon.projectiles[i], j);
				j = j + 1;
			}
		}
		i = i + 1;
	}
}
