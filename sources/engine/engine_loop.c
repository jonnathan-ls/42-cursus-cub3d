/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/20 16:17:39 by jlacerda         ###   ########.fr       */
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
	ft_player_move(eng);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_LEFT))
		ft_player_rotate(eng, -eng->player.rot_speed * delta_time * 60.0);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_RIGHT))
		ft_player_rotate(eng, eng->player.rot_speed * delta_time * 60.0);
	ft_player_mouse_rotate(eng);
	ft_minimap_toggle(eng, mlx_is_key_down(eng->mlx, MLX_KEY_M),
		&eng->minimap_toggle_prev);
	ft_minimap_zoom(eng,
		mlx_is_key_down(eng->mlx, MLX_KEY_KP_ADD)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_EQUAL),
		mlx_is_key_down(eng->mlx, MLX_KEY_KP_SUBTRACT)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_MINUS));
	ft_cast_all_rays(eng);
	ft_minimap_draw(eng);
}

void	ft_engine_close(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (eng && eng->mlx)
		mlx_close_window(eng->mlx);
}

void	ft_engine_loop(t_engine *eng)
{
	if (!eng || !eng->mlx)
		return ;
	mlx_close_hook(eng->mlx, ft_engine_close, eng);
	mlx_loop_hook(eng->mlx, frame_hook, eng);
	mlx_loop(eng->mlx);
}
