/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:36 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:46:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"

/**
 * Renders single vertical wall strip at screen column.
 * @param eng Pointer to engine structure.
 * @param x Screen column index.
 */
static void	render_wall(t_engine *eng, int x)
{
	t_ray	ray;
	int		wall_h;
	int		start;
	int		end;
	double	center_y;

	configure_raycast_initialization(eng, &ray, x);
	calculate_raycast_direction(&ray, &eng->player);
	setup_dda(&ray, &eng->player);
	perform_dda(eng, &ray);
	calculate_distances(&ray, &eng->player);
	if (eng->z_buffer)
		eng->z_buffer[x] = ray.perp_dist;
	wall_h = calculate_wall_height(&ray, eng->window_height);
	center_y = (double)eng->window_height / 2.0 - eng->player.pitch
		* ((double)eng->window_height / 4.0);
	start = -wall_h / 2 + (int)center_y;
	end = wall_h / 2 + (int)center_y;
	if (start < 0)
		start = 0;
	if (end >= eng->window_height)
		end = eng->window_height - 1;
	render_wall_strip(eng, &ray, start, end);
}

/**
 * Casts rays for all screen columns to render frame.
 * @param eng Pointer to engine structure.
 */
void	cast_all_rays(t_engine *eng)
{
	int	x;

	x = 0;
	while (x < eng->window_width)
	{
		render_wall(eng, x);
		x = x + 1;
	}
}
