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

/**
 * Applies shading intensity to RGBA color.
 * @param color Original color value.
 * @param intensity Shading intensity (0.0-1.0).
 * @return Shaded color value.
 */
static uint32_t	apply_shading(uint32_t color, float intensity)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = extract_color_channel(color, COLOR_SHIFT_RED);
	green = extract_color_channel(color, COLOR_SHIFT_GREEN);
	blue = extract_color_channel(color, COLOR_SHIFT_BLUE);
	alpha = extract_color_channel(color, 0);
	red = (uint8_t)(red * intensity);
	green = (uint8_t)(green * intensity);
	blue = (uint8_t)(blue * intensity);
	return (build_rgba_color(red, green, blue, alpha));
}

/**
 * Combines distance and side shading on color.
 * @param col Original color value.
 * @param side Wall side (0 for X, 1 for Y).
 * @param distance Distance from player to wall.
 * @return Final shaded color.
 */
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

/**
 * Gets texture pixel with shading applied.
 * @param tex Pointer to texture.
 * @param tx Texture X coordinate.
 * @param pos Texture Y position (can be fractional).
 * @param ray Pointer to ray for shading calculation.
 * @return Shaded pixel color.
 */
uint32_t	shaded_pixel_from_pos(
	mlx_texture_t *tex, int tx, double pos, t_ray *ray)
{
	int			ty;
	uint32_t	col;
	uint32_t	shaded;

	if (!tex)
		return (0x000000FF);
	ty = (int)pos;
	if (ty < TEXTURE_CLAMP_MIN)
		ty = TEXTURE_CLAMP_MIN;
	if (ty >= (int)tex->height)
		ty = (int)tex->height - TEXTURE_CLAMP_ONE;
	col = get_texture_pixel(tex, tx, ty);
	shaded = shade_with_distance(col, ray->side, ray->perp_dist);
	return (shaded);
}
