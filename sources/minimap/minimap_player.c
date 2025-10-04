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
#include <MLX42/MLX42.h>
#include <math.h>

static void	compute_player_params(
	int square_size, t_minimap_player_params *output)
{
	int	computed_length;

	computed_length = square_size / 8;
	if (computed_length < 1)
		computed_length = 1;
	output->length = computed_length;
	output->half_width = computed_length / 4;
	if (output->half_width < 1)
		output->half_width = 1;
	output->dx_screen = 0.0;
	output->dy_screen = -1.0;
	output->perp_x = -output->dy_screen;
	output->perp_y = output->dx_screen;
}

static void	draw_player_strip(t_engine *engine,
	int center_x, int center_y, t_minimap_player_params *p)
{
	int	step;
	int	inner_offset;
	int	cx_step;
	int	cy_step;
	int	current_half;

	step = 0;
	while (step <= p->length)
	{
		cx_step = center_x + (int)(p->dx_screen * (double)step);
		cy_step = center_y + (int)(p->dy_screen * (double)step);
		current_half = p->half_width - (p->half_width * step) / (p->length + 1);
		if (current_half < 0)
			current_half = 0;
		inner_offset = -current_half;
		while (inner_offset <= current_half)
		{
			mlx_put_pixel(engine->img.frame,
				cx_step + (int)(p->perp_x * (double)inner_offset),
				cy_step + (int)(p->perp_y * (double)inner_offset),
				MINIMAP_DIR_COLOR);
			inner_offset = inner_offset + 1;
		}
		step = step + 1;
	}
}

void	draw_minimap_player(t_engine *engine,
		int square_left, int square_top, int square_size)
{
	t_minimap_player_params	params;
	int						center_x;
	int						center_y;

	center_x = square_left + square_size / 2;
	center_y = square_top + square_size / 2;
	compute_player_params(square_size, &params);
	draw_player_strip(engine, center_x, center_y, &params);
}
