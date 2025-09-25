/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:59 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/24 21:49:42 by jlacerda         ###   ########.fr       */
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
	mlx_set_cursor_mode(eng->mlx, MLX_MOUSE_DISABLED);
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
	eng->player.mouse_x = WIN_WIDTH / 2;
	eng->player.mouse_y = WIN_HEIGHT / 2;
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
	zero_engine(eng);
	if (init_window_image(eng) != 0)
	{
		ft_engine_destroy(eng);
		return (-1);
	}
	init_map_dims(eng, cfg);
	init_player_colors(eng, cfg);
	if (ft_load_textures(eng, cfg) != 0)
	{
		ft_engine_destroy(eng);
		return (-1);
	}
	if (ft_doors_init(eng) != 0)
	{
		ft_engine_destroy(eng);
		return (-1);
	}
	ft_minimap_init(eng);
	return (0);
}
