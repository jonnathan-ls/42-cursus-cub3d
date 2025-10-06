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

void	draw_minimap_player(t_engine *engine, t_minimap_draw_info *info)
{
	t_minimap_player_params	params;
	int						center_x;
	int						center_y;

	if (!engine || !info)
		return ;
	center_x = info->left + info->size / CENTER_FACTOR;
	center_y = info->top + info->size / CENTER_FACTOR;
	compute_player_params(info->size, &params);
	draw_player_strip(engine, center_x, center_y, &params);
}
