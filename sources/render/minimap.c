/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>
#include <stdint.h>

static void	minimap_draw_player(t_engine *eng, int scale)
{
	int	center_x;
	int	center_y;
	int	size;
	int	dx;
	int	dy;

	center_x = (int)(eng->player.pos_x * scale) + MINIMAP_OFFSET;
	center_y = (int)(eng->player.pos_y * scale) + MINIMAP_OFFSET;
	size = scale / 2;
	dx = -size;
	while (dx <= size)
	{
		dy = -size;
		while (dy <= size)
		{
			mlx_put_pixel(eng->img.frame,
				center_x + dx, center_y + dy,
				MINIMAP_PLAYER_COLOR);
			dy++;
		}
		dx++;
	}
}

void	handle_minimap_toggle(t_engine *eng)
{
	int	key_pressed;

	key_pressed = mlx_is_key_down(eng->mlx, MLX_KEY_M);
	if (!eng)
		return ;
	if (key_pressed && !eng->minimap_toggle)
		eng->minimap_visible = !eng->minimap_visible;
	eng->minimap_toggle = key_pressed;
}

void	handle_minimap_zoom(t_engine *eng)
{
	int	scale;
	int	zoom_in;
	int	zoom_out;

	if (!eng)
		return ;
	zoom_in = mlx_is_key_down(eng->mlx, MLX_KEY_KP_ADD)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_EQUAL);
	zoom_out = mlx_is_key_down(eng->mlx, MLX_KEY_KP_SUBTRACT)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_MINUS);
	if (!zoom_in && !zoom_out)
		return ;
	if (!check_key_press_cooldown())
		return ;
	scale = eng->minimap_scale;
	if (zoom_in && scale < MINIMAP_MAX_SCALE)
		scale = scale + 1;
	if (zoom_out && scale > MINIMAP_MIN_SCALE)
		scale = scale - 1;
	eng->minimap_scale = scale;
}

void	minimap_draw(t_engine *eng)
{
	int	reserved_width;
	int	reserved_height;
	int	fit_w;
	int	fit_h;
	int	final_scale;

	if (!eng || !eng->img.frame || !eng->map || !eng->minimap_visible)
		return ;
	reserved_width = eng->win_w / MINIMAP_RESERVED_DIV;
	reserved_height = eng->win_h / MINIMAP_RESERVED_DIV;
	fit_w = reserved_width / eng->map_w;
	fit_h = reserved_height / eng->map_h;
	final_scale = fit_w;
	if (fit_h < final_scale)
		final_scale = fit_h;
	if (final_scale < MINIMAP_MIN_SCALE)
		final_scale = MINIMAP_MIN_SCALE;
	if (eng->minimap_scale >= MINIMAP_MIN_SCALE
		&& eng->minimap_scale < final_scale)
		final_scale = eng->minimap_scale;
	minimap_render_cells(eng, final_scale);
	minimap_draw_player(eng, final_scale);
}

void	minimap_init(t_engine *eng)
{
	if (!eng)
		return ;
	eng->minimap_scale = 3;
	eng->minimap_visible = 1;
	eng->minimap_toggle = 0;
	minimap_init_exploration(eng);
}
