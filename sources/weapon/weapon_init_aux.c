/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_init_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:58:41 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

void	init_default_values(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	eng->weapon.weapon_texture = NULL;
	eng->weapon.projectile_texture = NULL;
	eng->weapon.death_texture = NULL;
	eng->weapon.weapon_frames = 1;
	eng->weapon.projectile_frames = 1;
	eng->weapon.death_frames = 1;
	eng->weapon.weapon_frame_width = 64;
	eng->weapon.projectile_frame_width = 64;
	eng->weapon.death_frame_width = 64;
	eng->weapon.current_weapon_frame = 0;
	eng->weapon.weapon_anim_timer = 0.0;
	eng->weapon.shoot_cooldown = 0.0;
}

void	set_weapon_frame_width(void *param)
{
	t_engine	*eng;
	int			weapon_frames;

	eng = (t_engine *)param;
	weapon_frames = eng->weapon.weapon_frames;
	if (!eng->weapon.weapon_texture)
		return ;
	if (weapon_frames <= 0)
		return ;
	eng->weapon.weapon_frame_width = eng->weapon.weapon_texture->width
		/ weapon_frames;
}

void	set_projectile_frame_width(void *param)
{
	t_engine	*eng;
	int			projectile_frames;

	eng = (t_engine *)param;
	projectile_frames = eng->weapon.projectile_frames;
	if (!eng->weapon.projectile_texture)
		return ;
	if (projectile_frames <= 0)
		return ;
	eng->weapon.projectile_frame_width = eng->weapon.projectile_texture->width
		/ projectile_frames;
}

void	set_death_frame_width(void *param)
{
	t_engine	*eng;
	int			death_frames;

	eng = (t_engine *)param;
	death_frames = eng->weapon.death_frames;
	if (!eng->weapon.death_texture)
		return ;
	if (death_frames <= 0)
		return ;
	eng->weapon.death_frame_width
		= eng->weapon.death_texture->width / death_frames;
}

void	free_weapon_system(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng)
		return ;
}
