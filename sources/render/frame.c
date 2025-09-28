/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:36 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"

static void	cast_column(t_engine *eng, int x)
{
	t_ray	ray;
	int		wall_h;
	int		start;
	int		end;
	double	center_y;

	init_ray(eng, &ray, x);
	calculate_ray_dir(&ray, &eng->player);
	setup_dda(&ray, &eng->player);
	perform_dda(eng, &ray);
	calculate_distances(&ray, &eng->player);
	wall_h = calculate_wall_height(&ray, eng->win_h);
	center_y = (double)eng->win_h / 2.0 - eng->player.pitch
		* ((double)eng->win_h / 4.0);
	start = -wall_h / 2 + (int)center_y;
	end = wall_h / 2 + (int)center_y;
	if (start < 0)
		start = 0;
	if (end >= eng->win_h)
		end = eng->win_h - 1;
	render_wall_strip(eng, &ray, start, end);
}

void	cast_all_rays(t_engine *eng)
{
	int	x;

	x = 0;
	while (x < eng->win_w)
	{
		cast_column(eng, x);
		x++;
	}
}

void	render_walls(t_engine *eng)
{
	if (!eng)
		return ;
}

void	update_image_buffer(t_engine *eng)
{
	if (!eng)
		return ;
}
