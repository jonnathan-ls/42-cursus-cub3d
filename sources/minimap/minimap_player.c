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

static void	compute_player_params(t_engine *engine,
	int square_size, t_minimap_player_params *out)
{
	int	len;

	len = square_size / 8;
	if (len < 1)
		len = 1;
	out->length = len;
	out->half_width = len / 4;
	if (out->half_width < 1)
		out->half_width = 1;
	out->dx_screen = engine->player.dir_x * 1.0;
	out->dy_screen = - (engine->player.dir_x * engine->player.dir_x
			+ engine->player.dir_y * engine->player.dir_y);
	out->perp_x = -out->dy_screen;
	out->perp_y = out->dx_screen;
}

static void	draw_player_strip(t_engine *engine,
	int center_x, int center_y, t_minimap_player_params *p)
{
	int	step;
	int	inner_offset;
	int	cx_step;
	int	cy_step;

	step = 0;
	while (step <= p->length)
	{
		cx_step = center_x + (int)(p->dx_screen * (double)step);
		cy_step = center_y + (int)(p->dy_screen * (double)step);
		inner_offset = -p->half_width;
		while (inner_offset <= p->half_width)
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
	compute_player_params(engine, square_size, &params);
	draw_player_strip(engine, center_x, center_y, &params);
}
