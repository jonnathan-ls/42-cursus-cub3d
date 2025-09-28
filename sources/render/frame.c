/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:52:36 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/27 21:28:27 by jlacerda         ###   ########.fr       */
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

	ft_init_ray(eng, &ray, x);
	ft_calculate_ray_dir(&ray, &eng->player);
	ft_setup_dda(&ray, &eng->player);
	ft_perform_dda(eng, &ray);
	ft_calculate_distances(&ray, &eng->player);
	wall_h = ft_calculate_wall_height(&ray, eng->win_h);
	center_y = (double)eng->win_h / 2.0 - eng->player.pitch
		* ((double)eng->win_h / 4.0);
	start = -wall_h / 2 + (int)center_y;
	end = wall_h / 2 + (int)center_y;
	if (start < 0)
		start = 0;
	if (end >= eng->win_h)
		end = eng->win_h - 1;
	ft_render_wall_strip(eng, &ray, start, end);
}

void	ft_cast_all_rays(t_engine *eng)
{
	int	x;

	x = 0;
	while (x < eng->win_w)
	{
		cast_column(eng, x);
		x++;
	}
}

void	ft_render_walls(t_engine *eng)
{
	if (!eng)
		return ;
}

void	ft_update_image_buffer(t_engine *eng)
{
	if (!eng)
		return ;
}
