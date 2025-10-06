/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 03:09:07 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "raycast.h"
#include "render.h"
#include "minimap.h"
#include "sprite.h"

/**
 * Processes player input and updates per frame.
 * @param eng Pointer to engine structure.
 * @param delta_time Time elapsed since last frame.
 */
static void	handle_frame_updates(t_engine *eng, double delta_time)
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
 * Renders all UI elements on top of the scene.
 * @param eng Pointer to engine structure.
 */
static void	draw_interface(t_engine *eng)
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
 * Renders 3D scene with walls, sprites and projectiles.
 * @param eng Pointer to engine structure.
 */
static void	render_scene(t_engine *eng)
{
	cast_all_rays(eng);
	render_sprites(eng);
	render_projectiles(eng);
}

/**
 * Main frame update hook called each frame.
 * @param param Pointer to engine structure.
 */
static void	frame_hook(void *param)
{
	t_engine	*eng;
	double		delta_time;

	eng = (t_engine *)param;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eng->mlx);
	if (eng->player.game_over)
		return ;
	delta_time = eng->mlx->delta_time;
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
	render_scene(eng);
	handle_minimap_exploration(eng);
	handle_menu_view(eng);
	draw_interface(eng);
}

/**
 * Starts main game loop with hooks configured.
 * @param eng Pointer to engine structure.
 */
void	engine_loop(t_engine *eng)
{
	if (!eng || !eng->mlx)
		return ;
	mlx_close_hook(eng->mlx, close_engine, eng);
	mlx_loop_hook(eng->mlx, frame_hook, eng);
	mlx_loop(eng->mlx);
}
