/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_gameplay.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 01:43:59 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "player.h"
#include "raycast.h"
#include "render.h"
#include "minimap.h"

/**
 * @brief Handles all gameplay updates per frame.
 *
 * Processes player movement, sprite updates, enemy AI, weapon systems,
 * collision detection, and UI interactions during active gameplay.
 *
 * @param eng Pointer to engine structure.
 * @param delta_time Time elapsed since last frame.
 */
void	handle_gameplay_updates(t_engine *eng, double delta_time)
{
	handle_frame_updates(eng, delta_time);
	update_sprites(eng, delta_time);
	update_enemy_movement(eng, delta_time);
	update_projectiles(eng, delta_time);
	handle_weapon_shoot(eng);
	check_sprite_interactions(eng);
	check_projectile_hits(eng);
	handle_minimap_view(eng);
	handle_minimap_zoom(eng);
	handle_fullmap_view(eng);
	handle_door_updates(eng);
	handle_win_screen(eng);
	handle_lose_screen(eng);
}

/**
 * @brief Processes player input and updates per frame.
 *
 * Handles player movement, rotation via keyboard and mouse, and door
 * interaction during active gameplay.
 *
 * @param eng Pointer to engine structure.
 * @param delta_time Time elapsed since last frame.
 */
void	handle_frame_updates(t_engine *eng, double delta_time)
{
	double	rotation;

	if (!eng)
		return ;
	handle_player_movement(eng);
	rotation = eng->player.rot_speed * delta_time * 60.0;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_LEFT))
		handle_player_rotation(eng, -rotation);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_RIGHT))
		handle_player_rotation(eng, rotation);
	handle_door_interaction(eng);
	handle_player_rotation_by_mouse(eng);
}

/**
 * @brief Renders all UI elements on top of the scene.
 *
 * Draws minimap or full map, health bar, weapon sprite, menu overlay,
 * and damage indicators.
 *
 * @param eng Pointer to engine structure.
 */
void	draw_interface(t_engine *eng)
{
	if (eng->fullmap_visible)
		draw_full_map(eng);
	else
		draw_minimap(eng);
	draw_health_bar(eng);
	render_weapon(eng);
	if (eng->menu_visible && eng->tex.menu && eng->frame)
		draw_menu_overlay(eng);
	render_damage_overlay(eng);
}

/**
 * @brief Renders 3D scene with walls, sprites and projectiles.
 *
 * Performs raycasting twice (with and without door collision) and
 * renders all visible sprites and projectiles.
 *
 * @param eng Pointer to engine structure.
 */
void	render_scene(t_engine *eng)
{
	eng->ignore_doors = 1;
	cast_all_rays(eng);
	eng->ignore_doors = 0;
	cast_all_rays(eng);
	render_sprites(eng);
	render_projectiles(eng);
}
