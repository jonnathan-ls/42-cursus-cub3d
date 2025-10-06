/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

/**
 * @brief Advances weapon animation to next frame with looping.
 *
 * @param eng Engine structure containing weapon animation data.
 */
static void	advance_weapon_frame(t_engine *eng)
{
	eng->weapon.current_weapon_frame++;
	if (eng->weapon.current_weapon_frame >= eng->weapon.weapon_frames)
		eng->weapon.current_weapon_frame = 0;
	eng->weapon.weapon_anim_timer = 0.0;
}

/**
 * @brief Updates weapon animation timer and advances frames.
 *
 * @param eng Engine structure containing weapon animation data.
 * @param delta Delta time for frame-independent animation.
 */
static void	update_weapon_anim(t_engine *eng, double delta)
{
	eng->weapon.weapon_anim_timer += delta;
	if (eng->weapon.weapon_anim_timer >= 0.1)
		advance_weapon_frame(eng);
}

/**
 * @brief Advances projectile animation to next frame with looping.
 *
 * @param eng Engine structure containing projectile animation data.
 * @param proj Projectile to advance animation for.
 */
static void	advance_projectile_frame(t_engine *eng, t_projectile *proj)
{
	proj->current_frame++;
	if (proj->current_frame >= eng->weapon.projectile_frames)
		proj->current_frame = 0;
	proj->anim_timer = 0.0;
}

/**
 * @brief Moves projectile and deactivates on wall collision.
 *
 * @param eng Engine structure containing map data.
 * @param proj Projectile to move.
 * @param delta Delta time for frame-independent movement.
 */
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

/**
 * @brief Updates all active projectiles and weapon animation.
 *
 * @param param Engine structure cast from void pointer.
 * @param delta Delta time for frame-independent updates.
 */
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
