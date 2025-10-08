/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/07 22:46:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "shared.h"
#include "constants.h"

/**
 * Calculates adjusted screen center Y accounting for pitch.
 * @param eng Pointer to engine structure.
 * @return Center Y coordinate.
 */
static double	get_center_y(t_engine *eng)
{
	double	center_y;
	double	win_height;

	win_height = (double)eng->window_height;
	center_y = win_height / CENTER_DIVISOR - eng->player.pitch
		* (win_height / PITCH_FACTOR);
	return (center_y);
}

/**
 * Draws single pixel of wall strip with door offset.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @param pixel Pointer to pixel data structure.
 * @param y Screen Y coordinate.
 */
static void	put_pixel_strip(
	t_engine *eng, t_ray *ray, t_pixel *pixel, int y)
{
	int			target_x;
	uint32_t	color;

	target_x = ray->x;
	if (ray->hit_type == 'D' && pixel->shift > 0)
	{
		if (ray->x + pixel->shift >= 0
			&& ray->x + pixel->shift < eng->window_width)
			target_x = ray->x + pixel->shift;
	}
	color = shaded_pixel_from_pos(pixel->texture,
			pixel->texture_x, pixel->position, ray);
	mlx_put_pixel(eng->frame, target_x, y, color);
}

/**
 * Draws complete vertical texture strip for wall.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @param rng Array with start and end Y coordinates.
 * @param tex Pointer to texture to render.
 */
static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int		y;
	int		texture_height;
	t_pixel	pixel;
	double	step;

	if (!tex)
		return ;
	pixel.texture = tex;
	pixel.texture_x = calculate_texture_x(ray, tex,
			calculate_wall_x(eng, ray));
	texture_height = calculate_wall_height(ray, eng->window_height);
	if (texture_height <= TEXTURE_CLAMP_MIN)
		texture_height = TEXTURE_CLAMP_ONE;
	pixel.shift = get_door_texture_offset(eng, ray->map_x, ray->map_y);
	step = (double)tex->height / (double)texture_height;
	pixel.position = ((double)(rng[0] + texture_height / CENTER_FACTOR)
			- get_center_y(eng)) * step;
	y = rng[0];
	while (y <= rng[1])
	{
		put_pixel_strip(eng, ray, &pixel, y);
		pixel.position = pixel.position + step;
		y = y + 1;
	}
}

/**
 * Renders wall strip with ceiling and floor.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @param start Starting Y coordinate.
 * @param end Ending Y coordinate.
 */
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
