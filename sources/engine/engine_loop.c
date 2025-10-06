/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 01:31:13 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"

/**
 * @brief Main frame update hook called each frame.
 *
 * Handles game state transitions, escape key, and delegates to appropriate
 * rendering functions based on current state (start, playing, win, lose).
 *
 * @param param Pointer to engine structure.
 */
static void	frame_hook(void *param)
{
	t_engine	*eng;
	double		delta_time;

	eng = (t_engine *)param;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eng->mlx);
	if (!eng->game_started && eng->tex.start)
	{
		draw_screen_overlay(eng, eng->tex.start);
		handle_start_screen(eng);
		return ;
	}
	if (eng->player.game_over == 1 && eng->tex.lose)
		return (draw_screen_overlay(eng, eng->tex.lose));
	if (eng->player.game_over == 2 && eng->tex.win)
		return (draw_screen_overlay(eng, eng->tex.win));
	delta_time = eng->mlx->delta_time;
	handle_gameplay_updates(eng, delta_time);
	render_scene(eng);
	handle_minimap_exploration(eng);
	handle_menu_view(eng);
	draw_interface(eng);
}

/**
 * @brief Starts main game loop with hooks configured.
 *
 * Configures close and loop hooks for the MLX42 window and enters the
 * main event loop.
 *
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
