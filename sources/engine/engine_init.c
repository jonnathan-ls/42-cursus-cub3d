/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:59 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 19:19:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "minimap.h"
#include "sprite.h"
#include "shared.h"
#include <MLX42/MLX42.h>

static int	init_cursor_image(t_engine *eng)
{
	uint32_t	*pixels;
	int			center;

	eng->cursor = mlx_new_image(eng->mlx, 32, 32);
	if (!eng->cursor)
		return (-1);
	pixels = (uint32_t *)eng->cursor->pixels;
	center = 16;
	draw_circle(pixels, center, center, 8);
	pixels[center * 32 + center] = 0xFFFFFFFF;
	pixels[center * 32 + center - 1] = 0xFFFFFFFF;
	pixels[center * 32 + center + 1] = 0xFFFFFFFF;
	pixels[(center - 1) * 32 + center] = 0xFFFFFFFF;
	pixels[(center + 1) * 32 + center] = 0xFFFFFFFF;
	if (mlx_image_to_window(eng->mlx, eng->cursor, WIN_WIDTH / 2 - 16,
			WIN_HEIGHT / 2 - 16) < 0)
		return (-1);
	return (0);
}

static void	config_init_player(t_engine *eng, t_config *cfg)
{
	eng->ceiling_color = (uint32_t)cfg->ceiling_color.rgba;
	eng->floor_color = (uint32_t)cfg->floor_color.rgba;
	eng->player.pos_x = cfg->map.player_x + 0.5;
	eng->player.pos_y = cfg->map.player_y + 0.5;
	eng->player.move_speed = MOVEMENT_SPEED;
	eng->player.rot_speed = ROTATION_SPEED;
	eng->player.mouse_x = eng->window_width / 2;
	eng->player.mouse_y = eng->window_height / 2;
	eng->player.pitch = 0.0;
	eng->player.pitch_factor = 0.5;
	eng->player.health = 100;
	eng->player.game_over = 0;
	eng->player.damage_cooldown = 0.0;
	eng->player.is_taking_damage = 0;
	set_player_direction(eng, cfg->map.player_dir);
}

static int	init_window_image(t_engine *eng)
{
	eng->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", 1);
	if (!eng->mlx)
		return (-1);
	eng->frame = mlx_new_image(eng->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!eng->frame)
		return (-1);
	if (mlx_image_to_window(eng->mlx, eng->frame, 0, 0) < 0)
		return (-1);
	if (init_cursor_image(eng) != 0)
		return (-1);
	mlx_set_cursor_mode(eng->mlx, MLX_MOUSE_HIDDEN);
	apply_window_scale(eng);
	eng->z_buffer = mm_alloc(eng->window_width, sizeof(double));
	if (!eng->z_buffer)
		return (-1);
	return (0);
}

static int	configure_engine_base(t_engine *eng, t_config *cfg)
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
	eng->map_width = cfg->map.width;
	eng->map_height = cfg->map.height;
	config_init_player(eng, cfg);
	return (0);
}

int	configure_engine(t_engine *eng, t_config *cfg)
{
	if (configure_engine_base(eng, cfg) != 0)
		return (-1);
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
	init_sprites(eng, cfg->textures.sprites, cfg->textures.sprite_count);
	init_weapon_system(eng);
	return (0);
}
