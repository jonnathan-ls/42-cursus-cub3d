/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/03 00:16:14 by jlacerda         ###   ########.fr       */
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

	center_y = (double)eng->win_h / 2.0 - eng->player.pitch
		* ((double)eng->win_h / 4.0);
	return (center_y);
}

static void	put_pixel_strip(
	t_engine *eng, t_ray *ray, t_pixel *pixel, int y)
{
	if (ray->hit_type == 'D'
		&& pixel->shift > 0
		&& ray->x + pixel->shift >= 0
		&& ray->x + pixel->shift < eng->win_w)
	{
		mlx_put_pixel(eng->img.frame, ray->x + pixel->shift, y,
			shaded_pixel_from_pos(pixel->tex, pixel->tx, pixel->pos, ray));
	}
	else
		mlx_put_pixel(eng->img.frame, ray->x, y,
			shaded_pixel_from_pos(pixel->tex, pixel->tx, pixel->pos, ray));
}

static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int		y;
	int		th;
	t_pixel	pixel;

	if (!tex)
		return ;
	pixel.tex = tex;
	pixel.tx = calculate_texture_x(ray, tex, calculate_wall_x(eng, ray));
	th = calculate_wall_height(ray, eng->win_h);
	if (th <= 0)
		th = 1;
	pixel.shift = get_door_texture_offset(eng, ray->map_x, ray->map_y);
	pixel.pos = (double)(rng[0] + th / 2 - (int)get_center_y(eng))
		*((double)tex->height / (double)th);
	y = rng[0];
	while (y <= rng[1])
	{
		put_pixel_strip(eng, ray, &pixel, y);
		pixel.pos += (double)tex->height / (double)th;
		y++;
	}
}

void	render_wall_strip(t_engine *eng, t_ray *ray, int start, int end)
{
	mlx_texture_t	*tex;
	int				rng[2];

	if (start < 0)
		start = 0;
	if (end >= eng->win_h)
		end = eng->win_h - 1;
	render_ceiling_floor(eng, ray, start, end);
	tex = get_wall_texture(eng, ray);
	if (!tex)
		return ;
	rng[0] = start;
	rng[1] = end;
	draw_strip(eng, ray, rng, tex);
}
