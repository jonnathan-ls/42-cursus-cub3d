/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:00:00 by auto              #+#    #+#             */
/*   Updated: 2025/10/01 00:45:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include "shared.h"
#include <MLX42/MLX42.h>
#include <math.h>

/**
 * @brief Computes player arrow rendering parameters.
 *
 * Calculates arrow length, width, and direction vectors based on minimap
 * size and player orientation.
 *
 * @param size Minimap size.
 * @param output Parameter structure to populate.
 */
static void	compute_player_params(int size, t_minimap_player_params *output)
{
	int	computed_length;

	computed_length = size / DIRECTION_ARROW_DIVISOR;
	if (computed_length < MIN_ARROW_LENGTH)
		computed_length = MIN_ARROW_LENGTH;
	output->length = computed_length;
	output->half_width = computed_length / ARROW_WIDTH_DIVISOR;
	if (output->half_width < MIN_ARROW_WIDTH)
		output->half_width = MIN_ARROW_WIDTH;
	output->dx_screen = 0.0;
	output->dy_screen = -1.0;
	output->perp_x = -output->dy_screen;
	output->perp_y = output->dx_screen;
}

/**
 * @brief Draws a line segment of the player direction arrow.
 *
 * Renders a horizontal cross-section of the arrow at the specified step
 * position with appropriate width.
 *
 * @param engine Engine structure containing frame buffer.
 * @param p Player arrow parameters.
 * @param cx_step Center X coordinate of the line.
 * @param cy_step Center Y coordinate of the line.
 */
static void	draw_arrow_line(t_engine *engine, t_minimap_player_params *p,
	int cx_step, int cy_step)
{
	int	inner_offset;
	int	pixel_x;
	int	pixel_y;

	inner_offset = -p->half_width;
	while (inner_offset <= p->half_width)
	{
		pixel_x = cx_step + (int)(p->perp_x * (double)inner_offset);
		pixel_y = cy_step + (int)(p->perp_y * (double)inner_offset);
		mlx_put_pixel(engine->frame, pixel_x, pixel_y,
			MINIMAP_DIRECTION_COLOR);
		inner_offset = inner_offset + 1;
	}
}

/**
 * @brief Draws the complete player direction arrow.
 *
 * Iterates through arrow length, drawing progressively narrower lines
 * to create a tapered arrow shape pointing forward.
 *
 * @param engine Engine structure containing frame buffer.
 * @param center_x Center X coordinate of the arrow.
 * @param center_y Center Y coordinate of the arrow.
 * @param p Player arrow parameters.
 */
static void	draw_player_strip(t_engine *engine,
	int center_x, int center_y, t_minimap_player_params *p)
{
	int	step;
	int	cx_step;
	int	cy_step;

	step = 0;
	while (step <= p->length)
	{
		cx_step = center_x + (int)(p->dx_screen * (double)step);
		cy_step = center_y + (int)(p->dy_screen * (double)step);
		p->half_width = p->length / ARROW_WIDTH_DIVISOR - (p->length
				/ ARROW_WIDTH_DIVISOR * step) / (p->length
				+ TEXTURE_CLAMP_ONE);
		if (p->half_width < TEXTURE_CLAMP_MIN)
			p->half_width = TEXTURE_CLAMP_MIN;
		draw_arrow_line(engine, p, cx_step, cy_step);
		step = step + 1;
	}
}

/**
 * @brief Draws the player direction indicator.
 *
 * Computes center position and renders an arrow indicating player
 * position and facing direction. Can be used for both minimap and fullmap.
 * If dir_x and dir_y are both zero, uses default upward direction (minimap).
 * Otherwise, calculates angle from direction vectors (fullmap).
 *
 * @param engine Engine structure containing frame buffer.
 * @param info Drawing information with position and size.
 * @param dir_x Player direction X (0 for minimap default).
 * @param dir_y Player direction Y (0 for minimap default).
 */
void	draw_player_on_map(t_engine *engine, t_map_draw_info *info,
	double dir_x, double dir_y)
{
	t_minimap_player_params	params;
	int						center_x;
	int						center_y;
	double					angle;

	if (!engine || !info)
		return ;
	center_x = info->left + info->size / CENTER_FACTOR;
	center_y = info->top + info->size / CENTER_FACTOR;
	compute_player_params(info->size, &params);
	if (dir_x != 0.0 || dir_y != 0.0)
	{
		angle = atan2(dir_y, dir_x);
		params.dx_screen = cos(angle);
		params.dy_screen = sin(angle);
		params.perp_x = -params.dy_screen;
		params.perp_y = params.dx_screen;
	}
	draw_player_strip(engine, center_x, center_y, &params);
}
