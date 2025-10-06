/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 21:52:12 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "shared.h"
#include "constants.h"

static double	get_center_y(t_engine *eng)
{
	double	center_y;
	double	win_height;

	win_height = (double)eng->window_height;
	center_y = win_height / CENTER_DIVISOR - eng->player.pitch
		* (win_height / PITCH_FACTOR);
	return (center_y);
}

static void	put_pixel_strip(
	t_engine *eng, t_ray *ray, t_pixel *pixel, int y)
{
	if (ray->hit_type == 'D'
		&& pixel->shift > 0
		&& ray->x + pixel->shift >= 0
		&& ray->x + pixel->shift < eng->window_width)
	{
		mlx_put_pixel(eng->frame, ray->x + pixel->shift, y,
			shaded_pixel_from_pos(
				pixel->texture, pixel->texture_x, pixel->position, ray));
	}
	else
		mlx_put_pixel(eng->frame, ray->x, y,
			shaded_pixel_from_pos(
				pixel->texture, pixel->texture_x, pixel->position, ray));
}

static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int		y;
	int		texture_height;
	t_pixel	pixel;

	if (!tex)
		return ;
	pixel.texture = tex;
	pixel.texture_x = calculate_texture_x(ray, tex,
			calculate_wall_x(eng, ray));
	texture_height = calculate_wall_height(ray, eng->window_height);
	if (texture_height <= TEXTURE_CLAMP_MIN)
		texture_height = TEXTURE_CLAMP_ONE;
	pixel.shift = get_door_texture_offset(eng, ray->map_x, ray->map_y);
	pixel.position = (double)(rng[0] + texture_height / CENTER_FACTOR
			- (int)get_center_y(eng)) *((double)tex->height
			/ (double)texture_height);
	y = rng[0];
	while (y <= rng[1])
	{
		put_pixel_strip(eng, ray, &pixel, y);
		pixel.position = pixel.position + (double)tex->height
			/ (double)texture_height;
		y = y + 1;
	}
}

void	render_wall_strip(t_engine *eng, t_ray *ray, int start, int end)
{
	mlx_texture_t	*tex;
	int				rng[2];

	if (start < TEXTURE_CLAMP_MIN)
		start = TEXTURE_CLAMP_MIN;
	if (end >= eng->window_height)
		end = eng->window_height - TEXTURE_CLAMP_ONE;
	render_ceiling_floor(eng, ray, start, end);
	tex = get_wall_texture(eng, ray);
	if (!tex)
		return ;
	rng[0] = start;
	rng[1] = end;
	draw_strip(eng, ray, rng, tex);
}
