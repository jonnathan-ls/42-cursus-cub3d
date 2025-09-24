/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/24 00:57:31 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"
#include "constants.h"

static float	calculate_distance_shade(double distance)
{
	float	fog_factor;
	float	smooth_factor;

	if (distance <= FOG_DISTANCE_START)
		return (1.0f);
	if (distance >= FOG_DISTANCE_MAX)
		return (FOG_MIN_INTENSITY);
	fog_factor = (distance - FOG_DISTANCE_START)
		/ (FOG_DISTANCE_MAX - FOG_DISTANCE_START);
	smooth_factor = fog_factor * fog_factor * (3.0f - 2.0f * fog_factor);
	return (1.0f - smooth_factor * (1.0f - FOG_MIN_INTENSITY));
}

static uint32_t	apply_distance_shading(uint32_t color, double distance)
{
	float	intensity;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	intensity = calculate_distance_shade(distance);
	r = (uint8_t)((color >> 24) & 0xFF);
	g = (uint8_t)((color >> 16) & 0xFF);
	b = (uint8_t)((color >> 8) & 0xFF);
	a = (uint8_t)(color & 0xFF);
	r = (uint8_t)(r * intensity);
	g = (uint8_t)(g * intensity);
	b = (uint8_t)(b * intensity);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	ft_get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint32_t	color;
	uint8_t		*pixel_ptr;

	pixel_ptr = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

static uint32_t	calc_floor_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.floor)
		return (eng->floor_color);
	row_distance = (double)eng->win_h / (2.0 * y - eng->win_h);
	*distance = row_distance;
	floor_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	floor_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(floor_x * eng->tex.floor->width) % eng->tex.floor->width;
	tex_y = (int)(floor_y * eng->tex.floor->height) % eng->tex.floor->height;
	if (tex_x < 0)
		tex_x += eng->tex.floor->width;
	if (tex_y < 0)
		tex_y += eng->tex.floor->height;
	return (ft_get_texture_pixel(eng->tex.floor, tex_x, tex_y));
}

static uint32_t	calc_ceil_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.ceiling)
		return (eng->ceil_color);
	row_distance = (double)eng->win_h / (eng->win_h - 2.0 * y);
	*distance = row_distance;
	ceil_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	ceil_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(ceil_x * eng->tex.ceiling->width) % eng->tex.ceiling->width;
	tex_y = (int)(ceil_y * eng->tex.ceiling->height) % eng->tex.ceiling->height;
	if (tex_x < 0)
		tex_x += eng->tex.ceiling->width;
	if (tex_y < 0)
		tex_y += eng->tex.ceiling->height;
	return (ft_get_texture_pixel(eng->tex.ceiling, tex_x, tex_y));
}

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
			color = calc_ceil_texture(eng, y, ray, &distance);
			color = apply_distance_shading(color, distance);
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
			color = calc_floor_texture(eng, y, ray, &distance);
			color = apply_distance_shading(color, distance);
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
