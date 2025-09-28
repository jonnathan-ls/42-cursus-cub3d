/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shade.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"
#include "constants.h"

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
	smooth_factor = fog_factor * fog_factor * (3.0f - 2.0f * fog_factor);
	return (1.0f - smooth_factor * (1.0f - FOG_MIN_INTENSITY));
}

uint32_t	apply_distance_shading(uint32_t color, double distance)
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
