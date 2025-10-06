/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shade.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"
#include "constants.h"
#include "shared.h"

float	calculate_distance_shade(double distance)
{
	float	fog_factor;
	float	smooth_factor;

	if (distance <= FOG_DISTANCE_START)
		return (1.0f);
	if (distance >= FOG_DISTANCE_MAX)
		return (FOG_MIN_INTENSITY);
	fog_factor = (distance - FOG_DISTANCE_START)
		/ (FOG_DISTANCE_MAX - FOG_DISTANCE_START);
	smooth_factor = fog_factor * fog_factor
		* (SMOOTH_FACTOR_A - SMOOTH_FACTOR_B * fog_factor);
	return (1.0f - smooth_factor * (1.0f - FOG_MIN_INTENSITY));
}

uint32_t	apply_distance_shading(uint32_t color, double distance)
{
	float	intensity;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	intensity = calculate_distance_shade(distance);
	red = extract_color_channel(color, COLOR_SHIFT_RED);
	green = extract_color_channel(color, COLOR_SHIFT_GREEN);
	blue = extract_color_channel(color, COLOR_SHIFT_BLUE);
	alpha = extract_color_channel(color, 0);
	red = (uint8_t)(red * intensity);
	green = (uint8_t)(green * intensity);
	blue = (uint8_t)(blue * intensity);
	return (build_rgba_color(red, green, blue, alpha));
}
