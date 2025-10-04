/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:22 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>
#include <stdint.h>

void	handle_minimap_zoom(t_engine *eng)
{
	int	delta;

	delta = 0;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_KP_ADD)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_EQUAL))
		delta = 1;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_KP_SUBTRACT)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_MINUS))
		delta = delta - 1;
	if (delta == 0)
		return ;
	if (!check_key_press_cooldown())
		return ;
	if (eng->minimap_scale + delta < MINIMAP_MIN_SCALE)
		return ;
	if (eng->minimap_scale + delta > MINIMAP_MAX_SCALE)
		return ;
	eng->minimap_scale = eng->minimap_scale + delta;
}

void	handle_minimap_view(t_engine *eng)
{
	int	key_pressed;

	if (!eng)
		return ;
	key_pressed = mlx_is_key_down(eng->mlx, MLX_KEY_M);
	if (key_pressed && !eng->minimap_toggle)
		eng->minimap_visible = !eng->minimap_visible;
	eng->minimap_toggle = key_pressed;
}

static void	compute_minimap_context(t_engine *eng,
		t_minimap *map, int square_size)
{
	int	usable;
	int	base_scale;
	int	final_scale;

	usable = square_size - 2 * 2;
	if (usable < 1)
		usable = 1;
	base_scale = usable / 10;
	if (base_scale < MINIMAP_MIN_SCALE)
		base_scale = MINIMAP_MIN_SCALE;
	final_scale = base_scale * eng->minimap_scale;
	if (final_scale < MINIMAP_MIN_SCALE)
		final_scale = MINIMAP_MIN_SCALE;
	if (final_scale > usable)
		final_scale = usable;
	map->final_scale = final_scale;
	map->left = MINIMAP_OFFSET;
	map->top = eng->win_h - MINIMAP_OFFSET - square_size;
	map->size = square_size;
}

void	draw_minimap(t_engine *eng)
{
	int			square_size;
	t_minimap	map;

	if (!eng || !eng->img.frame || !eng->map || !eng->minimap_visible)
		return ;
	square_size = eng->win_w / 10;
	if (square_size < 8)
		square_size = 8;
	draw_minimap_frame(eng, MINIMAP_OFFSET,
		eng->win_h - MINIMAP_OFFSET - square_size,
		square_size);
	compute_minimap_context(eng, &map, square_size);
	draw_minimap_background(eng, &map);
	render_minimap_pixels(eng, &map);
	draw_minimap_player(eng, map.left, map.top,
		map.size);
}

void	configure_minimap(t_engine *eng)
{
	if (!eng)
		return ;
	eng->minimap_scale = 3;
	eng->minimap_visible = 1;
	eng->minimap_toggle = 0;
	eng->fullmap_visible = 0;
	eng->fullmap_toggle = 0;
	initialize_minimap_exploration(eng);
}
