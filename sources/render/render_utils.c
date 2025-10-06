/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:53:39 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "constants.h"
#include "shared.h"

static double	calculate_row_distance(t_engine *eng, int y, int is_floor)
{
	double	win_h;
	double	center;
	double	den;
	double	tmp;

	win_h = (double)eng->window_height;
	center = win_h / CENTER_DIVISOR - eng->player.pitch
		* (win_h / PITCH_FACTOR);
	if (is_floor)
	{
		tmp = (double)y - center;
		den = CENTER_DIVISOR * tmp;
	}
	else
	{
		tmp = center - (double)y;
		den = CENTER_DIVISOR * tmp;
	}
	if (den == 0.0)
		den = EPSILON;
	return (win_h / den);
}

double	calculate_wall_x(t_engine *eng, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = eng->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = eng->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - (int)wall_x);
}

uint32_t	get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint32_t	color;
	uint8_t		*pixel_ptr;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;

	pixel_ptr = &tex->pixels[(tex_y * tex->width + tex_x) * RGBA_BYTES];
	red = pixel_ptr[0];
	green = pixel_ptr[1];
	blue = pixel_ptr[2];
	color = build_rgba_color(red, green, blue, pixel_ptr[3]);
	return (color);
}

uint32_t	calculate_floor_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.floor)
		return (eng->floor_color);
	row_distance = calculate_row_distance(eng, y, 1);
	*distance = row_distance;
	floor_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	floor_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(floor_x * eng->tex.floor->width) % eng->tex.floor->width;
	tex_y = (int)(floor_y * eng->tex.floor->height) % eng->tex.floor->height;
	if (tex_x < TEXTURE_CLAMP_MIN)
		tex_x = tex_x + eng->tex.floor->width;
	if (tex_y < TEXTURE_CLAMP_MIN)
		tex_y = tex_y + eng->tex.floor->height;
	return (get_texture_pixel(eng->tex.floor, tex_x, tex_y));
}

uint32_t	calculate_ceiling_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.ceiling)
		return (eng->ceiling_color);
	row_distance = calculate_row_distance(eng, y, 0);
	*distance = row_distance;
	ceil_x = atan2(ray->ray_dir_y, ray->ray_dir_x);
	ceil_x = (ceil_x + PI) / (CENTER_DIVISOR * PI);
	tex_x = (int)(ceil_x * eng->tex.ceiling->width) % eng->tex.ceiling->width;
	ceil_y = (double)(eng->window_height - y) / (double)eng->window_height;
	tex_y = (int)(ceil_y * eng->tex.ceiling->height)
		% eng->tex.ceiling->height;
	if (tex_x < TEXTURE_CLAMP_MIN)
		tex_x = tex_x + eng->tex.ceiling->width;
	if (tex_y < TEXTURE_CLAMP_MIN)
		tex_y = tex_y + eng->tex.ceiling->height;
	return (get_texture_pixel(eng->tex.ceiling, tex_x, tex_y));
}
