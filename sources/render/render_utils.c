/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:53:39 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/24 23:13:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "constants.h"

double	ft_calc_wall_x(t_engine *eng, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = eng->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = eng->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - (int)wall_x);
}

uint32_t	ft_get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint32_t	color;
	uint8_t		*pixel_ptr;

	pixel_ptr = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

uint32_t	ft_calc_floor_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.floor)
		return (eng->floor_color);
	row_distance = (double)eng->win_h / (2.0 * y - eng->win_h);
	*distance = row_distance;
	floor_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	floor_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(floor_x * eng->tex.floor->width) % eng->tex.floor->width;
	tex_y = (int)(floor_y * eng->tex.floor->height) % eng->tex.floor->height;
	if (tex_x < 0)
		tex_x += eng->tex.floor->width;
	if (tex_y < 0)
		tex_y += eng->tex.floor->height;
	return (ft_get_texture_pixel(eng->tex.floor, tex_x, tex_y));
}

uint32_t	ft_calc_ceil_texture(t_engine *eng, int y, t_ray *ray,
	double *distance)
{
	double	row_distance;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;

	if (!eng->tex.ceiling)
		return (eng->ceil_color);
	row_distance = (double)eng->win_h / (eng->win_h - 2.0 * y);
	*distance = row_distance;
	ceil_x = eng->player.pos_x + row_distance * ray->ray_dir_x;
	ceil_y = eng->player.pos_y + row_distance * ray->ray_dir_y;
	tex_x = (int)(ceil_x * eng->tex.ceiling->width) % eng->tex.ceiling->width;
	tex_y = (int)(ceil_y * eng->tex.ceiling->height) % eng->tex.ceiling->height;
	if (tex_x < 0)
		tex_x += eng->tex.ceiling->width;
	if (tex_y < 0)
		tex_y += eng->tex.ceiling->height;
	return (ft_get_texture_pixel(eng->tex.ceiling, tex_x, tex_y));
}
