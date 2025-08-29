/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:59 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 21:49:17 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include <MLX42/MLX42.h>

static void	set_player_dir(t_engine *eng, char dir)
{
	eng->player.dir_x = (dir == 'E') - (dir == 'W');
	eng->player.dir_y = (dir == 'S') - (dir == 'N');
	eng->player.plane_x = ((dir == 'N') - (dir == 'S')) * PLANE_FACTOR;
	eng->player.plane_y = ((dir == 'E') - (dir == 'W')) * PLANE_FACTOR;
}

static int	init_window_image(t_engine *eng)
{
	eng->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", 1);
	if (!eng->mlx)
		return (-1);
	eng->img.frame = mlx_new_image(eng->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!eng->img.frame)
		return (-1);
	if (mlx_image_to_window(eng->mlx, eng->img.frame, 0, 0) < 0)
		return (-1);
	return (0);
}

static void	init_player_colors(t_engine *eng, t_config *cfg)
{
	eng->ceil_color = (uint32_t)cfg->ceiling_color.rgba;
	eng->floor_color = (uint32_t)cfg->floor_color.rgba;
	eng->player.pos_x = cfg->map.player_x + 0.5;
	eng->player.pos_y = cfg->map.player_y + 0.5;
	eng->player.move_speed = MOVE_SPEED;
	eng->player.rot_speed = ROT_SPEED;
	set_player_dir(eng, cfg->map.player_dir);
}

static void	init_map_dims(t_engine *eng, t_config *cfg)
{
	eng->map = cfg->map.grid;
	eng->map_w = cfg->map.width;
	eng->map_h = cfg->map.height;
	eng->win_w = WIN_WIDTH;
	eng->win_h = WIN_HEIGHT;
}

int	ft_engine_init(t_engine *eng, t_config *cfg)
{
	if (!eng || !cfg)
		return (-1);
	if (init_window_image(eng) != 0)
		return (-1);
	init_map_dims(eng, cfg);
	init_player_colors(eng, cfg);
	if (ft_load_textures(eng, cfg) != 0)
		return (-1);
	return (0);
}
