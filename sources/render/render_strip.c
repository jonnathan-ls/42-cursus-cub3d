/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:39 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/27 23:15:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "cub3d.h"
#include "constants.h"

static double	get_center_y(t_engine *eng)
{
	double	center_y;

	center_y = (double)eng->win_h / 2.0 - eng->player.pitch
		* ((double)eng->win_h / 4.0);
	return (center_y);
}

static void	ft_put_pixel_strip(
	t_engine *eng, t_ray *ray, struct s_pixel_ctx *ctx, int y)
{
	if (ray->hit_type == 'D'
		&& ctx->shift > 0
		&& ray->x + ctx->shift >= 0
		&& ray->x + ctx->shift < eng->win_w)
	{
		mlx_put_pixel(eng->img.frame, ray->x + ctx->shift, y,
			ft_shaded_pixel_from_pos(ctx->tex, ctx->tx, ctx->pos, ray));
	}
	else
		mlx_put_pixel(eng->img.frame, ray->x, y,
			ft_shaded_pixel_from_pos(ctx->tex, ctx->tx, ctx->pos, ray));
}

static void	draw_strip(t_engine *eng, t_ray *ray, int *rng, mlx_texture_t *tex)
{
	int					y;
	int					th;
	struct s_pixel_ctx	ctx;

	if (!tex)
		return ;
	ctx.tex = tex;
	ctx.tx = ft_calculate_texture_x(ray, tex, ft_calc_wall_x(eng, ray));
	th = ft_calculate_wall_height(ray, eng->win_h);
	if (th <= 0)
		th = 1;
	ctx.shift = ft_get_door_texture_offset(eng, ray->map_x, ray->map_y);
	ctx.pos = (double)(rng[0] + th / 2 - (int)get_center_y(eng))
		*((double)tex->height / (double)th);
	y = rng[0];
	while (y <= rng[1])
	{
		ft_put_pixel_strip(eng, ray, &ctx, y);
		ctx.pos += (double)tex->height / (double)th;
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
	ft_render_ceiling_floor(eng, ray, start, end);
	tex = ft_get_wall_texture(eng, ray);
	if (!tex)
		return ;
	rng[0] = start;
	rng[1] = end;
	draw_strip(eng, ray, rng, tex);
}
