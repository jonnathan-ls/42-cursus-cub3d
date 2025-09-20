/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/19 23:39:33 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"

static void	draw_ceil_floor(t_engine *eng, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start && y < eng->win_h)
	{
		mlx_put_pixel(eng->img.frame, x, y, eng->ceil_color);
		y++;
	}
	y = end + 1;
	while (y < eng->win_h)
	{
		mlx_put_pixel(eng->img.frame, x, y, eng->floor_color);
		y++;
	}
}

static double	calc_wall_x(t_engine *eng, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = eng->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = eng->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - (int)wall_x);
}

static uint32_t	shade(uint32_t col, int side)
{
	if (side == 1)
		return ((col & 0xFF000000) | (((col >> 16 & 0xFF) * 60
					/ 100) << 16) | (((col >> 8 & 0xFF) * 60
					/ 100) << 8) | ((col & 0xFF) * 60 / 100));
	return (col);
}

static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int		y;
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;

	tex_x = ft_calculate_texture_x(ray, tex, calc_wall_x(eng, ray));
	tex_y = ft_calculate_wall_height(ray, eng->win_h);
	if (tex_y <= 0)
		tex_y = 1;
	step = (double)tex->height / (double)tex_y;
	tex_pos = (double)(rng[0] + tex_y / 2 - eng->win_h / 2) * step;
	y = rng[0];
	while (y <= rng[1])
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		mlx_put_pixel(eng->img.frame, ray->x, y, shade(((uint32_t *)tex->pixels)
			[tex_y * tex->width + tex_x], ray->side));
		tex_pos += step;
		y++;
	}
}

void	ft_render_wall_strip(t_engine *eng, t_ray *ray, int start, int end)
{
	mlx_texture_t	*tex;
	int				rng[2];

	if (start < 0)
		start = 0;
	if (end >= eng->win_h)
		end = eng->win_h - 1;
	draw_ceil_floor(eng, ray->x, start, end);
	tex = ft_get_wall_texture(eng, ray);
	if (!tex)
		return ;
	rng[0] = start;
	rng[1] = end;
	draw_strip(eng, ray, rng, tex);
}
