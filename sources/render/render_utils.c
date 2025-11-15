/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:53:39 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/14 20:58:29 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "constants.h"
#include "shared.h"

/**
 * Calculates distance from player to floor or ceiling row.
 * @param eng Pointer to engine structure.
 * @param y Screen Y coordinate.
 * @param is_floor 1 for floor, 0 for ceiling.
 * @return Row distance.
 */
static double	calculate_row_distance(t_engine *eng, int y, int is_floor)
{
	double	win_h;
	double	center;
	double	den;
	double	tmp;

	win_h = (double)eng->window_height;
	center = eng->horizon_y;
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

/**
 * Calculates fractional wall intersection point.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @return Wall X coordinate (0.0-1.0).
 */
double	calculate_wall_x(t_engine *eng, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = eng->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = eng->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - (int)wall_x);
}

/**
 * Extracts RGBA pixel from texture at coordinates.
 * @param tex Pointer to texture.
 * @param tex_x Texture X coordinate.
 * @param tex_y Texture Y coordinate.
 * @return RGBA color value.
 */
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

/**
 * Calculates floor texture color at screen position.
 * @param eng Pointer to engine structure.
 * @param y Screen Y coordinate.
 * @param ray Pointer to ray structure.
 * @param distance Pointer to store calculated distance.
 * @return Floor texture color or solid color.
 */
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

/**
 * Calculates ceiling texture color using tiling.
 * @param eng Pointer to engine structure.
 * @param y Screen Y coordinate.
 * @param ray Pointer to ray structure.
 * @param distance Pointer to store calculated distance.
 * @return Ceiling texture color or solid color.
 */
uint32_t	calculate_ceiling_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	ceiling_x;
	double	ceiling_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.ceiling)
		return (eng->ceiling_color);
	row_distance = calculate_row_distance(eng, y, 0);
	*distance = row_distance;
	ceiling_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	ceiling_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(ceiling_x * eng->tex.ceiling->width)
		% eng->tex.ceiling->width;
	tex_y = (int)(ceiling_y * eng->tex.ceiling->height)
		% eng->tex.ceiling->height;
	if (tex_x < TEXTURE_CLAMP_MIN)
		tex_x = tex_x + eng->tex.ceiling->width;
	if (tex_y < TEXTURE_CLAMP_MIN)
		tex_y = tex_y + eng->tex.ceiling->height;
	return (get_texture_pixel(eng->tex.ceiling, tex_x, tex_y));
}
