/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:46:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"
#include "constants.h"

/**
 * Draws ceiling pixels above wall.
 * @param eng Pointer to engine structure.
 * @param x Screen column index.
 * @param start Y coordinate where wall starts.
 * @param ray Pointer to ray structure.
 */
static void	draw_ceiling_pixels(t_engine *eng, int x, int start, t_ray *ray)
{
	int			y;
	uint32_t	color;
	double		distance;

	y = 0;
	while (y < start && y < eng->window_height)
	{
		if (eng->tex.ceiling)
		{
			color = calculate_ceiling_texture(eng, y, ray, &distance);
			color = apply_distance_shading(color, distance);
		}
		else
			color = eng->ceiling_color;
		mlx_put_pixel(eng->frame, x, y, color);
		y = y + 1;
	}
}

/**
 * Draws floor pixels below wall.
 * @param eng Pointer to engine structure.
 * @param x Screen column index.
 * @param end Y coordinate where wall ends.
 * @param ray Pointer to ray structure.
 */
static void	draw_floor_pixels(t_engine *eng, int x, int end, t_ray *ray)
{
	int			y;
	uint32_t	color;
	double		distance;

	y = end + 1;
	while (y < eng->window_height)
	{
		if (eng->tex.floor)
		{
			color = calculate_floor_texture(eng, y, ray, &distance);
			color = apply_distance_shading(color, distance);
		}
		else
			color = eng->floor_color;
		mlx_put_pixel(eng->frame, x, y, color);
		y = y + 1;
	}
}

/**
 * Renders ceiling and floor for wall strip.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @param start Y coordinate where wall starts.
 * @param end Y coordinate where wall ends.
 */
void	render_ceiling_floor(t_engine *eng, t_ray *ray, int start, int end)
{
	draw_ceiling_pixels(eng, ray->x, start, ray);
	draw_floor_pixels(eng, ray->x, end, ray);
}
