/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/24 23:12:37 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"
#include "constants.h"

static void	draw_ceiling_pixels(t_engine *eng, int x, int start, t_ray *ray)
{
	int			y;
	uint32_t	color;
	double		distance;

	y = 0;
	while (y < start && y < eng->win_h)
	{
		if (eng->tex.ceiling)
		{
			color = ft_calc_ceil_texture(eng, y, ray, &distance);
			color = ft_apply_distance_shading(color, distance);
		}
		else
			color = eng->ceil_color;
		mlx_put_pixel(eng->img.frame, x, y, color);
		y++;
	}
}

static void	draw_floor_pixels(t_engine *eng, int x, int end, t_ray *ray)
{
	int			y;
	uint32_t	color;
	double		distance;

	y = end + 1;
	while (y < eng->win_h)
	{
		if (eng->tex.floor)
		{
			color = ft_calc_floor_texture(eng, y, ray, &distance);
			color = ft_apply_distance_shading(color, distance);
		}
		else
			color = eng->floor_color;
		mlx_put_pixel(eng->img.frame, x, y, color);
		y++;
	}
}

void	ft_render_ceiling_floor(t_engine *eng, t_ray *ray, int start, int end)
{
	draw_ceiling_pixels(eng, ray->x, start, ray);
	draw_floor_pixels(eng, ray->x, end, ray);
}
