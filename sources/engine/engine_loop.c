/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:06:25 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "raycast.h"
#include "render.h"

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
	ft_cast_all_rays(eng);
}

void	ft_engine_loop(t_engine *eng)
{
	if (!eng || !eng->mlx)
		return ;
	mlx_loop_hook(eng->mlx, frame_hook, eng);
	mlx_loop(eng->mlx);
}
