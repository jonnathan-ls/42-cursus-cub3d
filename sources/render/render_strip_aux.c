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
	if (ty < TEXTURE_CLAMP_MIN)
		ty = TEXTURE_CLAMP_MIN;
	if (ty >= (int)tex->height)
		ty = (int)tex->height - TEXTURE_CLAMP_ONE;
	col = get_texture_pixel(tex, tx, ty);
	shaded = shade_with_distance(col, ray->side, ray->perp_dist);
	return (shaded);
}
