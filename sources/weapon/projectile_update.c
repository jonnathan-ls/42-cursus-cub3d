/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:58:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

static void	advance_weapon_frame(t_engine *eng)
{
	eng->weapon.current_weapon_frame++;
	if (eng->weapon.current_weapon_frame >= eng->weapon.weapon_frames)
		eng->weapon.current_weapon_frame = 0;
	eng->weapon.weapon_anim_timer = 0.0;
}

static void	update_weapon_anim(t_engine *eng, double delta)
{
	eng->weapon.weapon_anim_timer += delta;
	if (eng->weapon.weapon_anim_timer >= 0.1)
		advance_weapon_frame(eng);
}

static void	advance_projectile_frame(t_engine *eng, t_projectile *proj)
{
	proj->current_frame++;
	if (proj->current_frame >= eng->weapon.projectile_frames)
		proj->current_frame = 0;
	proj->anim_timer = 0.0;
}

static void	move_projectile(t_engine *eng, t_projectile *proj, double delta)
{
	proj->x += proj->dir_x * proj->speed * delta;
	proj->y += proj->dir_y * proj->speed * delta;
	proj->anim_timer += delta;
	if (proj->anim_timer >= 0.1)
		advance_projectile_frame(eng, proj);
	if (is_wall(eng, proj->x, proj->y))
		proj->active = 0;
}

void	update_projectiles(void *param, double delta)
{
	t_engine	*eng;
	int			i;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	update_weapon_anim(eng, delta);
	if (eng->weapon.shoot_cooldown > 0.0)
		eng->weapon.shoot_cooldown -= delta;
	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (eng->weapon.projectiles[i].active)
			move_projectile(eng, &eng->weapon.projectiles[i], delta);
		i++;
	}
}
