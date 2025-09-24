/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:30:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/23 22:34:48 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include "raycast.h"

static uint32_t	calc_floor_texture(t_engine *eng, int y, t_ray *ray)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.floor)
		return (eng->floor_color);
	row_distance = (double)eng->win_h / (2.0 * y - eng->win_h);
	floor_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	floor_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(floor_x * eng->tex.floor->width) % eng->tex.floor->width;
	tex_y = (int)(floor_y * eng->tex.floor->height) % eng->tex.floor->height;
	if (tex_x < 0)
		tex_x += eng->tex.floor->width;
	if (tex_y < 0)
		tex_y += eng->tex.floor->height;
	return (((uint32_t *)eng->tex.floor->pixels)
		[tex_y * eng->tex.floor->width + tex_x]);
}

static uint32_t	calc_ceil_texture(t_engine *eng, int y, t_ray *ray)
{
	double	row_distance;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.ceiling)
		return (eng->ceil_color);
	row_distance = (double)eng->win_h / (eng->win_h - 2.0 * y);
	ceil_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	ceil_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(ceil_x * eng->tex.ceiling->width) % eng->tex.ceiling->width;
	tex_y = (int)(ceil_y * eng->tex.ceiling->height) % eng->tex.ceiling->height;
	if (tex_x < 0)
		tex_x += eng->tex.ceiling->width;
	if (tex_y < 0)
		tex_y += eng->tex.ceiling->height;
	return (((uint32_t *)eng->tex.ceiling->pixels)
		[tex_y * eng->tex.ceiling->width + tex_x]);
}

static void	draw_ceiling_pixels(t_engine *eng, int x, int start, t_ray *ray)
{
	int			y;
	uint32_t	color;

	y = 0;
	while (y < start && y < eng->win_h)
	{
		if (eng->tex.ceiling)
			color = calc_ceil_texture(eng, y, ray);
		else
			color = eng->ceil_color;
		mlx_put_pixel(eng->img.frame, x, y, color);
		y++;
	}
}

static void	draw_floor_pixels(t_engine *eng, int x, int end, t_ray *ray)
{
	int			y;
	uint32_t	color;

	y = end + 1;
	while (y < eng->win_h)
	{
		if (eng->tex.floor)
			color = calc_floor_texture(eng, y, ray);
		else
			color = eng->floor_color;
		mlx_put_pixel(eng->img.frame, x, y, color);
		y++;
	}
}

void	ft_render_ceiling_floor(t_engine *eng, t_ray *ray, int start, int end)
{
	draw_ceiling_pixels(eng, ray->x, start, ray);
	draw_floor_pixels(eng, ray->x, end, ray);
}
