/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "raycast.h"
#include "render.h"
#include "minimap.h"

static void	frame_hook(void *param)
{
	t_engine	*eng;
	double		delta_time;

	eng = (t_engine *)param;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eng->mlx);
	delta_time = eng->mlx->delta_time;
	player_move(eng);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_LEFT))
		player_rotate(eng, -eng->player.rot_speed * delta_time * 60.0);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_RIGHT))
		player_rotate(eng, eng->player.rot_speed * delta_time * 60.0);
	handle_door_interaction(eng);
	player_mouse_rotate(eng);
	handle_minimap_toggle(eng);
	handle_minimap_zoom(eng);
	doors_update(eng);
	eng->ignore_doors = 1;
	cast_all_rays(eng);
	eng->ignore_doors = 0;
	cast_all_rays(eng);
	minimap_update_exploration(eng);
	minimap_draw(eng);
}

void	engine_close(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (eng && eng->mlx)
		mlx_close_window(eng->mlx);
}

void	engine_loop(t_engine *eng)
{
	if (!eng || !eng->mlx)
		return ;
	mlx_close_hook(eng->mlx, engine_close, eng);
	mlx_loop_hook(eng->mlx, frame_hook, eng);
	mlx_loop(eng->mlx);
}
