/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:59 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 20:36:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "minimap.h"
#include <MLX42/MLX42.h>

static int	init_cursor_image(t_engine *eng)
{
	uint32_t	*pixels;
	int			center;

	eng->img.cursor = mlx_new_image(eng->mlx, 32, 32);
	if (!eng->img.cursor)
		return (-1);
	pixels = (uint32_t *)eng->img.cursor->pixels;
	center = 16;
	draw_circle(pixels, center, center, 8);
	pixels[center * 32 + center] = 0xFFFFFFFF;
	pixels[center * 32 + center - 1] = 0xFFFFFFFF;
	pixels[center * 32 + center + 1] = 0xFFFFFFFF;
	pixels[(center - 1) * 32 + center] = 0xFFFFFFFF;
	pixels[(center + 1) * 32 + center] = 0xFFFFFFFF;
	if (mlx_image_to_window(eng->mlx, eng->img.cursor, WIN_WIDTH / 2 - 16,
			WIN_HEIGHT / 2 - 16) < 0)
		return (-1);
	return (0);
}

static void	apply_window_scale(t_engine *eng)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	if (!eng->fullscreen)
	{
		eng->win_w = WIN_WIDTH;
		eng->win_h = WIN_HEIGHT;
		return ;
	}
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	if (monitor_width > 0 && monitor_height > 0)
	{
		eng->win_w = monitor_width;
		eng->win_h = monitor_height;
		mlx_set_window_size(eng->mlx, eng->win_w, eng->win_h);
		if (eng->img.frame)
			mlx_resize_image(eng->img.frame, eng->win_w, eng->win_h);
	}
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
	if (init_cursor_image(eng) != 0)
		return (-1);
	mlx_set_cursor_mode(eng->mlx, MLX_MOUSE_HIDDEN);
	apply_window_scale(eng);
	return (0);
}

static void	config_init_player(t_engine *eng, t_config *cfg)
{
	eng->ceil_color = (uint32_t)cfg->ceiling_color.rgba;
	eng->floor_color = (uint32_t)cfg->floor_color.rgba;
	eng->player.pos_x = cfg->map.player_x + 0.5;
	eng->player.pos_y = cfg->map.player_y + 0.5;
	eng->player.move_speed = MOVEMENT_SPEED;
	eng->player.rot_speed = ROTATION_SPEED;
	eng->player.mouse_x = eng->win_w / 2;
	eng->player.mouse_y = eng->win_h / 2;
	eng->player.pitch = 0.0;
	eng->player.pitch_factor = 0.5;
	set_player_direction(eng, cfg->map.player_dir);
}

int	configure_engine(t_engine *eng, t_config *cfg)
{
	if (!eng || !cfg)
		return (-1);
	reset_engine_values(eng);
	mlx_set_setting(MLX_FULLSCREEN, eng->fullscreen);
	if (init_window_image(eng) != 0)
	{
		destroy_engine(eng);
		return (-1);
	}
	eng->map = cfg->map.grid;
	eng->map_w = cfg->map.width;
	eng->map_h = cfg->map.height;
	config_init_player(eng, cfg);
	if (configure_textures(eng, cfg) != 0)
	{
		destroy_engine(eng);
		return (-1);
	}
	if (configure_doors(eng) != 0)
	{
		destroy_engine(eng);
		return (-1);
	}
	configure_minimap(eng);
	return (0);
}
