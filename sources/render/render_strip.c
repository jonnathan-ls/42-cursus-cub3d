/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/27 21:28:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "cub3d.h"
#include "constants.h"

static uint32_t	apply_shading(uint32_t color, float intensity)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)((color >> 24) & 0xFF);
	g = (uint8_t)((color >> 16) & 0xFF);
	b = (uint8_t)((color >> 8) & 0xFF);
	a = (uint8_t)(color & 0xFF);
	r = (uint8_t)(r * intensity);
	g = (uint8_t)(g * intensity);
	b = (uint8_t)(b * intensity);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static uint32_t	shade_with_distance(uint32_t col, int side, double distance)
{
	float	distance_shade;
	float	side_shade;
	float	final_intensity;

	distance_shade = ft_calculate_distance_shade(distance);
	if (side == 1)
		side_shade = SIDE_SHADE_FACTOR;
	else
		side_shade = 1.0f;
	final_intensity = distance_shade * side_shade;
	return (apply_shading(col, final_intensity));
}

static double	get_center_y(t_engine *eng)
{
	double	center_y;

	center_y = (double)eng->win_h / 2.0
		- eng->player.pitch * ((double)eng->win_h / 4.0);
	return (center_y);
}

static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int		y;
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;

	tex_x = ft_calculate_texture_x(ray, tex, ft_calc_wall_x(eng, ray));
	tex_y = ft_calculate_wall_height(ray, eng->win_h);
	tex_y = ft_ternary_int(tex_y <= 0, 1, tex_y);
	step = (double)tex->height / (double)tex_y;
	tex_pos = (double)(rng[0] + tex_y / 2 - (int)get_center_y(eng)) *step;
	y = rng[0];
	while (y <= rng[1])
	{
		tex_y = (int)tex_pos;
		tex_y = ft_ternary_int(tex_y < 0, 0, tex_y);
		tex_y = ft_ternary_int(tex_y >= (int)tex->height, (int)tex->height - 1,
				tex_y);
		mlx_put_pixel(eng->img.frame, ray->x, y,
			shade_with_distance(ft_get_texture_pixel(tex, tex_x, tex_y),
				ray->side, ray->perp_dist));
		tex_pos += step;
		y++;
	}
}

void	ft_render_wall_strip(t_engine *eng, t_ray *ray, int start, int end)
{
	mlx_texture_t	*tex;
	int				rng[2];

	if (start < 0)
		start = 0;
	if (end >= eng->win_h)
		end = eng->win_h - 1;
	ft_render_ceiling_floor(eng, ray, start, end);
	tex = ft_get_wall_texture(eng, ray);
	if (!tex)
		return ;
	rng[0] = start;
	rng[1] = end;
	draw_strip(eng, ray, rng, tex);
}
