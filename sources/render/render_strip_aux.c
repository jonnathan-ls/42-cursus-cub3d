/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autoedit <autoedit@local>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:00:00 by autoedit         #+#    #+#             */
/*   Updated: 2025/09/27 23:00:00 by autoedit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "constants.h"
#include "shared.h"

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

	distance_shade = calculate_distance_shade(distance);
	if (side == 1)
		side_shade = SIDE_SHADE_FACTOR;
	else
		side_shade = 1.0f;
	final_intensity = distance_shade * side_shade;
	return (apply_shading(col, final_intensity));
}

uint32_t	shaded_pixel_from_pos(
	mlx_texture_t *tex, int tx, double pos, t_ray *ray)
{
	int			ty;
	uint32_t	col;
	uint32_t	shaded;

	ty = (int)pos;
	if (ty < 0)
		ty = 0;
	if (ty >= (int)tex->height)
		ty = (int)tex->height - 1;
	col = get_texture_pixel(tex, tx, ty);
	shaded = shade_with_distance(col, ray->side, ray->perp_dist);
	return (shaded);
}
