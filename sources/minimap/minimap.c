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
#include "shared.h"
#include <MLX42/MLX42.h>

/**
 * @brief Handles minimap zoom based on keyboard input.
 *
 * Monitors + and - keys (including numpad) to increase or decrease the
 * minimap scale within defined limits, applying cooldown to prevent
 * rapid changes.
 *
 * @param eng Engine structure containing minimap scale and input state.
 */
void	handle_minimap_zoom(t_engine *eng)
{
	int	delta;

	delta = 0;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_KP_ADD)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_EQUAL))
		delta = TEXTURE_CLAMP_ONE;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_KP_SUBTRACT)
		|| mlx_is_key_down(eng->mlx, MLX_KEY_MINUS))
		delta = delta - TEXTURE_CLAMP_ONE;
	if (delta == 0 || !check_key_press_cooldown())
		return ;
	if (!is_within_bounds(eng->minimap_scale + delta,
			MINIMAP_MIN_SCALE, MINIMAP_MAX_SCALE + TEXTURE_CLAMP_ONE))
		return ;
	eng->minimap_scale = eng->minimap_scale + delta;
}

/**
 * @brief Toggles minimap visibility on M key press.
 *
 * Detects M key press and toggles the minimap_visible flag, using a
 * toggle flag to prevent rapid state changes from continuous key press.
 *
 * @param eng Engine structure containing minimap visibility state.
 */
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

/**
 * @brief Computes minimap display parameters based on window size.
 *
 * Calculates the final scale, position, and dimensions of the minimap
 * based on the available square size, player scale, and defined limits.
 *
 * @param eng Engine structure containing window dimensions and scale.
 * @param map Minimap structure to populate with computed values.
 * @param square_size Size of the minimap square.
 */
static void	compute_minimap_context(t_engine *eng,
		t_minimap *map, int square_size)
{
	int	usable;
	int	base_scale;
	int	final_scale;

	usable = square_size - MINIMAP_BORDER_OFFSET;
	if (usable < TEXTURE_CLAMP_ONE)
		usable = TEXTURE_CLAMP_ONE;
	base_scale = usable / MINIMAP_SCALE_DIVISOR;
	if (base_scale < MINIMAP_MIN_SCALE)
		base_scale = MINIMAP_MIN_SCALE;
	final_scale = base_scale * eng->minimap_scale;
	if (final_scale < MINIMAP_MIN_SCALE)
		final_scale = MINIMAP_MIN_SCALE;
	if (final_scale > usable)
		final_scale = usable;
	map->final_scale = final_scale;
	map->left = MINIMAP_OFFSET;
	map->top = eng->window_height - MINIMAP_OFFSET - square_size;
	map->size = square_size;
}

/**
 * @brief Draws the minimap overlay on the frame.
 *
 * Computes minimap size and position, draws the frame, background, map
 * pixels, and player indicator if minimap is visible.
 *
 * @param eng Engine structure containing frame, map, and display state.
 */
void	draw_minimap(t_engine *eng)
{
	int				square_size;
	t_minimap		map;
	t_map_draw_info	info;

	if (!eng || !eng->frame || !eng->map || !eng->minimap_visible)
		return ;
	square_size = eng->window_width / MINIMAP_SIZE_DIVISOR;
	if (square_size < MINIMAP_MIN_SIZE)
		square_size = MINIMAP_MIN_SIZE;
	info.left = MINIMAP_OFFSET;
	info.top = eng->window_height - MINIMAP_OFFSET - square_size;
	info.size = square_size;
	draw_minimap_frame(eng, &info);
	compute_minimap_context(eng, &map, square_size);
	draw_minimap_background(eng, &map);
	render_minimap_pixels(eng, &map);
	draw_player_on_map(eng, &info, 0.0, 0.0);
}

/**
 * @brief Initializes minimap configuration and state.
 *
 * Sets default scale, visibility, toggle flags for minimap and fullmap,
 * and initializes the exploration tracking system.
 *
 * @param eng Engine structure to configure.
 */
void	configure_minimap(t_engine *eng)
{
	if (!eng)
		return ;
	eng->minimap_scale = DEFAULT_MINIMAP_SCALE;
	eng->minimap_visible = 1;
	eng->minimap_toggle = 0;
	eng->fullmap_visible = 0;
	eng->fullmap_toggle = 0;
	initialize_minimap_exploration(eng);
}
