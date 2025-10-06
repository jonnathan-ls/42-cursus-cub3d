/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:25:14 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"
#include "parser.h"
#include "constants.h"
#include <MLX42/MLX42.h>

static t_sprite_config	*find_sprite_by_category(t_engine *eng, int cat)
{
	int	i;

	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (eng->sprites.configs[i].type == cat)
			return (&eng->sprites.configs[i]);
		i = i + 1;
	}
	return (NULL);
}

static void	init_projectiles(t_weapon_system *weapon)
{
	int	i;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		weapon->projectiles[i].active = 0;
		weapon->projectiles[i].x = 0.0;
		weapon->projectiles[i].y = 0.0;
		weapon->projectiles[i].dir_x = 0.0;
		weapon->projectiles[i].dir_y = 0.0;
		weapon->projectiles[i].speed = PROJECTILE_SPEED;
		weapon->projectiles[i].damage = PROJECTILE_DAMAGE;
		weapon->projectiles[i].current_frame = 0;
		weapon->projectiles[i].anim_timer = 0.0;
		i = i + 1;
	}
}

static void	load_textures(t_engine *eng)
{
	t_sprite_config	*weapon_cfg;
	t_sprite_config	*projectile_cfg;
	t_sprite_config	*death_cfg;
	int				i;

	weapon_cfg = find_sprite_by_category(eng, SPRITE_TYPE_WEAPON);
	projectile_cfg = find_sprite_by_category(eng, SPRITE_TYPE_PROJECTILE);
	death_cfg = find_sprite_by_category(eng, SPRITE_TYPE_ENEMY_DEAD);
	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (weapon_cfg && eng->sprites.configs[i].type == SPRITE_TYPE_WEAPON)
			eng->weapon.weapon_texture = eng->sprites.textures[i];
		if (projectile_cfg && eng->sprites.configs[i].type
			== SPRITE_TYPE_PROJECTILE)
			eng->weapon.projectile_texture = eng->sprites.textures[i];
		if (death_cfg && eng->sprites.configs[i].type
			== SPRITE_TYPE_ENEMY_DEAD)
			eng->weapon.death_texture = eng->sprites.textures[i];
		i = i + 1;
	}
}

static void	set_frame_counts(t_engine *eng)
{
	t_sprite_config	*cfg;

	cfg = find_sprite_by_category(eng, SPRITE_TYPE_WEAPON);
	eng->weapon.weapon_frames = 1;
	if (cfg)
		eng->weapon.weapon_frames = cfg->frames;
	cfg = find_sprite_by_category(eng, SPRITE_TYPE_PROJECTILE);
	eng->weapon.projectile_frames = 1;
	if (cfg)
		eng->weapon.projectile_frames = cfg->frames;
	cfg = find_sprite_by_category(eng, SPRITE_TYPE_ENEMY_DEAD);
	eng->weapon.death_frames = 1;
	if (cfg)
		eng->weapon.death_frames = cfg->frames;
}

void	init_weapon_system(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	init_default_values(eng);
	init_projectiles(&eng->weapon);
	load_textures(eng);
	set_frame_counts(eng);
	set_weapon_frame_width(eng);
	set_projectile_frame_width(eng);
	set_death_frame_width(eng);
}
